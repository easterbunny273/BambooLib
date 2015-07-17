#ifndef GENERALDEFINITIONS_H
#define GENERALDEFINITIONS_H

#define BAMBOOLIB_VERSION "0.1"

#ifdef WIN32
	#ifdef BAMBOOLIB_EXPORTS
	#define BAMBOOLIB_DLL _declspec(dllexport)
	#else
	#define BAMBOOLIB_DLL _declspec(dllimport)
	#endif
#else
	#define BAMBOOLIB_DLL 
#endif

namespace BambooLib
{
    /*! \name Some general forward declarations */
    //@{
        class IIdentifyable;
        class ISerializer;
    //@}

    /*! \name Type declarations */
    //@{
        /// Each object gets an unique object id
        typedef unsigned long long t_objectID;

        /// Each class gets an unique class id
        typedef unsigned long long t_classID;
    //@}

    /*! \name Some constant variables */
    //@{
        const t_objectID INVALID_OBJECTID = 0;
    //@}
}

#endif // GENERALDEFINITIONS_H
