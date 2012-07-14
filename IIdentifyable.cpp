#include "IIdentifyable.h"
#include <iostream>
#include <cassert>

namespace BambooLib
{
    void IIdentifyable::Store(std::ostream &outStream,
                              ISerializer *pSerializer) const
    {
        std::cout << "store Start" << std::endl;
        pSerializer->StartObjectWriting();

        pSerializer->Serialize(outStream, GetClassID());
        pSerializer->Serialize(outStream, GetObjectID());

        ItlWriteToStream(outStream, pSerializer);

        pSerializer->StopObjectWriting(outStream);

        std::cout << "store Stop" << std::endl;
    }

    bool IIdentifyable::Restore(std::istream &inStream, ISerializer *pSerializer)
    {
        pSerializer->StartObjectReading();

        t_classID nClassID;
        t_objectID nObjectID;

        pSerializer->Unserialize(inStream, nClassID);
        pSerializer->Unserialize(inStream, nObjectID);

        assert (nClassID == m_nClassID);
        assert (nObjectID == m_nObjectID);

        bool bOk = (nClassID == m_nClassID && m_nObjectID == nObjectID);

        if (bOk)
            ItlReadFromStream(inStream, pSerializer);

        pSerializer->StopObjectReading(inStream, true);

        return bOk;
    }
}
