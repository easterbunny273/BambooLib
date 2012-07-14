#ifndef IIDENTIFYABLE_H
#define IIDENTIFYABLE_H

#include "CoreSystem.h"

namespace BambooLib
{
    class ISerializer;

    class IIdentifyable
    {
    public:
        IIdentifyable(t_classID nClassID, t_objectID nObjectID) : m_nClassID(nClassID), m_nObjectID(nObjectID) { CoreSystem::GetInstance()->RegisterObject(this); }
        IIdentifyable(t_classID nClassID) : m_nClassID(nClassID), m_nObjectID(CoreSystem::GetInstance()->GetNextFreeObjectID()) { CoreSystem::GetInstance()->RegisterObject(this); }

        virtual ~IIdentifyable() { CoreSystem::GetInstance()->UnregisterObject(this); }

        t_objectID GetObjectID() const { return m_nObjectID; }
        t_classID GetClassID() const { return m_nClassID; }

    protected:
        const t_classID   m_nClassID;
        const t_objectID  m_nObjectID;
    };


    template <typename T>
    class _TIIdentifyable_StaticInterfaceTester
    {
        void TestMethods()
        {
            T::Cast(nullptr);
            T::ClassID();
            T::CreateEmpty(0, 0);
        }
    };

    template <class T>
    class _TIdentifyable_PreDefinedMethods
    {
    public:
        static T * Cast(IIdentifyable *pObject) { return dynamic_cast<T*>(pObject); }
    };
}
#endif // IIDENTIFYABLE_H
