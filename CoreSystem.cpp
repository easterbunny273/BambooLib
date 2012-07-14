#include "CoreSystem.h"
#include "IIdentifyable.h"

#include <cassert>
#include <cstring>

BambooLib::CoreSystem::CoreSystem()
{
    m_nNextFreeObjectCode = 1;
}

BambooLib::CoreSystem *BambooLib::CoreSystem::GetInstance()
{
    static CoreSystem sInstance;

    return &sInstance;
}


BambooLib::t_classID BambooLib::CoreSystem::RegisterClass(const char *szClassName, void * pCreateMethod)
{
    assert (strlen(szClassName) == 8);

    long long int nClassID = 0;

    assert (sizeof(nClassID) >= 8);

    for (unsigned int i=0; i < 8; i++)
        nClassID += ((unsigned short int) szClassName[i]) << i;

    auto iter = m_mRegisteredClasses.find(nClassID);
    assert (iter == m_mRegisteredClasses.end());

    m_mRegisteredClasses[nClassID] = szClassName;
    m_mRegisteredCreateMethods[nClassID] = pCreateMethod;

    return (t_classID) (nClassID);
}


bool BambooLib::CoreSystem::RegisterObject(BambooLib::IIdentifyable *pObject)
{
    // get object id
    t_objectID nObjectID = pObject->GetObjectID();
    assert (nObjectID != INVALID_OBJECTID);

    // make sure that we don't return an already used object ID as free object ID (can happen due object (un)serialization)
    if (nObjectID >= m_nNextFreeObjectCode)
        m_nNextFreeObjectCode = nObjectID+1;

    // make sure object is not registered yet
    bool bOk = IsObjectRegistered(nObjectID) == false;
    assert (bOk);

    if (bOk)
    {
        // add into map
        m_mRegisteredObjects[nObjectID] = pObject;

        // inform pointers
        auto iter = m_sRegisteredPtrs.begin();

        while (iter != m_sRegisteredPtrs.end())
        {
            PtrIIdentifyable *pPtr = *iter;

            if (pPtr->id() == nObjectID)
                pPtr->OnObjectCreated();

            iter++;
        }
    }



    return bOk;
}

bool BambooLib::CoreSystem::UnregisterObject(BambooLib::IIdentifyable *pObject)
{
    // get object id
    t_objectID nObjectID = pObject->GetObjectID();

    assert (nObjectID != INVALID_OBJECTID);

    // make sure object is registered
    bool bOk = IsObjectRegistered(nObjectID);
    assert (bOk);

    // erase object
    m_mRegisteredObjects.erase(nObjectID);

    // inform pointers
    auto iter = m_sRegisteredPtrs.begin();

    while (iter != m_sRegisteredPtrs.end())
    {
        PtrIIdentifyable *pPtr = *iter;

        if (pPtr->id() == nObjectID)
            pPtr->OnObjectDeleted();

        iter++;
    }


    return bOk;
}

bool BambooLib::CoreSystem::RegisterPtrIIdentifyable(BambooLib::PtrIIdentifyable *pPtr)
{
    m_sRegisteredPtrs.insert(pPtr);
}

bool BambooLib::CoreSystem::UnregisterPtrIIdentifyable(BambooLib::PtrIIdentifyable *pPtr)
{
    m_sRegisteredPtrs.erase(pPtr);
}


bool BambooLib::CoreSystem::IsObjectRegistered(BambooLib::t_objectID nID)
{
    auto iterator = m_mRegisteredObjects.find(nID);

    return (iterator != m_mRegisteredObjects.end());
}

BambooLib::t_objectID BambooLib::CoreSystem::GetNextFreeObjectID()
{
    t_objectID nNextFree = m_nNextFreeObjectCode++;

    return nNextFree;

}

BambooLib::IIdentifyable *BambooLib::CoreSystem::GetObjectForObjectID(BambooLib::t_objectID nID)
{
    assert (IsObjectRegistered(nID));

    auto iterator = m_mRegisteredObjects.find(nID);

    if (iterator != m_mRegisteredObjects.end())
        return iterator->second;
    else
        return nullptr;
}

void *BambooLib::CoreSystem::GetCreateMethod(BambooLib::t_classID nClassID)
{
    assert (m_mRegisteredClasses.find(nClassID) != m_mRegisteredClasses.end());

    auto iterator = m_mRegisteredCreateMethods.find(nClassID);

    if (iterator != m_mRegisteredCreateMethods.end())
        return iterator->second;
    else
        return nullptr;
}


void BambooLib::PtrIIdentifyable::OnObjectDeleted()
{
    m_pObject = nullptr;
}

void BambooLib::PtrIIdentifyable::OnObjectCreated()
{
    m_pObject = CoreSystem::GetInstance()->GetObjectForObjectID(m_nObjectID);
}

BambooLib::PtrIIdentifyable::PtrIIdentifyable(BambooLib::t_objectID nObjectID) : m_nObjectID(nObjectID), m_pObject(nullptr)
{
    CoreSystem::GetInstance()->RegisterPtrIIdentifyable(this);
}

BambooLib::IIdentifyable *BambooLib::PtrIIdentifyable::ptr() const
{
    assert (m_pObject != nullptr);

    return m_pObject;
}

BambooLib::PtrIIdentifyable::PtrIIdentifyable(BambooLib::IIdentifyable *pPtr) : m_nObjectID(pPtr->GetObjectID()), m_pObject(pPtr)
{
    CoreSystem::GetInstance()->RegisterPtrIIdentifyable(this);
}

BambooLib::PtrIIdentifyable::~PtrIIdentifyable()
{
    CoreSystem::GetInstance()->UnregisterPtrIIdentifyable(this);
}




BambooLib::IIdentifyable *BambooLib::PtrIIdentifyable::operator ->() const
{
    //IIdentifyable *pPtr = ptr();

    return ptr();
}
