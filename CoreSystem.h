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

    const t_objectID INVALID_OBJECTID = 0;

    class CoreSystem
    {
    private:
        CoreSystem();

        std::map<t_objectID, IIdentifyable *>                   m_mRegisteredObjects;
        std::map<t_classID, const char *>                       m_mRegisteredClasses;
        std::map<t_classID, void *>     m_mRegisteredCreateMethods;

        t_objectID m_nNextFreeObjectCode;
    public:
        static CoreSystem * GetInstance();

        t_classID RegisterClass(const char *szClassName, void *pCreateMethod);

        bool RegisterObject(IIdentifyable *pObject);
        bool UnregisterObject(IIdentifyable *pObject);

        bool IsObjectRegistered(t_objectID nID);

        t_objectID GetNextFreeObjectID();

        IIdentifyable * GetObjectForObjectID(t_objectID nID);

        void * GetCreateMethod(t_classID nClassID);
    };
}


#endif // CORESYSTEM_H
