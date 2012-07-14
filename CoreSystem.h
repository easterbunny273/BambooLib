#ifndef CORESYSTEM_H
#define CORESYSTEM_H

#include <map>
#include <set>

namespace BambooLib
{
    class IIdentifyable;
    class ISerializer;


    typedef unsigned long long t_objectID;
    typedef unsigned long long t_classID;

    class PtrIIdentifyable
    {
        friend class CoreSystem;
    private:
        t_objectID      m_nObjectID;
        mutable IIdentifyable   *m_pObject;

        void OnObjectDeleted();
        void OnObjectCreated();
    public:
        PtrIIdentifyable(t_objectID nObjectID);
        PtrIIdentifyable(IIdentifyable *pPtr);

        ~PtrIIdentifyable();

        IIdentifyable * ptr() const;
        t_objectID id() const { return m_nObjectID; }

        IIdentifyable* operator->() const;
    };

    template <class T>
    class Ptr2IIdentifyable : public PtrIIdentifyable
    {
    public:
        Ptr2IIdentifyable(T * pPtr) : PtrIIdentifyable(pPtr) {}
        Ptr2IIdentifyable(t_objectID nObjectID) : PtrIIdentifyable(nObjectID) {}

        T * ptr2() const { return T::Cast(ptr()); }
        T * operator->() const { return ptr2(); }
    };

    const t_objectID INVALID_OBJECTID = 0;

    class CoreSystem
    {
    private:
        CoreSystem();

        std::map<t_objectID, IIdentifyable *>                   m_mRegisteredObjects;
        std::map<t_classID, const char *>                       m_mRegisteredClasses;
        std::map<t_classID, void *>     m_mRegisteredCreateMethods;

        std::set<PtrIIdentifyable *> m_sRegisteredPtrs;

        t_objectID m_nNextFreeObjectCode;
    public:
        static CoreSystem * GetInstance();

        t_classID RegisterClass(const char *szClassName, void *pCreateMethod);
        //t_classID RegisterCreateMethod(t_classID nClassID, void * pCreateMethod);

        bool RegisterObject(IIdentifyable *pObject);
        bool UnregisterObject(IIdentifyable *pObject);

        bool RegisterPtrIIdentifyable(PtrIIdentifyable *pPtr);
        bool UnregisterPtrIIdentifyable(PtrIIdentifyable *pPtr);

        bool IsObjectRegistered(t_objectID nID);

        t_objectID GetNextFreeObjectID();

        IIdentifyable * GetObjectForObjectID(t_objectID nID);

        void * GetCreateMethod(t_classID nClassID);
    };
}


#endif // CORESYSTEM_H
