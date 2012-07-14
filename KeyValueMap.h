/*
 * header file for Settings class
 * written by: christian moellinger <ch.moellinger@gmail.com>
 *             florian spechtenhauser <florian.spechtenhauser@gmail.com>
 *
 * 10/2010, Project "BambooIsland"
 * 03/2011, Project "Free Pool"
 * 07/2011, Project "Project Cube"
 * 05/2012, Project "BambooLib"
 */

#ifndef BAMBOOLIB_KEYVALUEMAP
#define BAMBOOLIB_KEYVALUEMAP

// Settings is a IXMLSerializeable-class
//#include "IXMLSerializeable.h"

// stl includes
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <ostream>
#include <istream>
#include <sstream>
#include <cstring>

// other includes
#include <glm/glm.hpp>
#include <memory>

#include "IStreamCoder.h"

// forward declerations
class TiXmlElement;

namespace BambooLib
{

class KeyValueMap //: public IXMLSerializeable
{
public:
    /*! \name Forward declerations */
    //@{
    class TGroup;

    typedef std::string TMultiVar;
    //@}

    /*! \name Public methods */
    //@{

    /// stores the given value
    template<class T> void SetValue(std::string sName, T Value)
    {
        std::stringstream Stream;

        static IStreamCoder Coder;
        Coder.ItlWrite(Stream, Value);

        m_mMultiMap[sName] = Stream.str();;
    }

    /// reads the wanted value to the given variable and returns true if successfull (if value was found)
    template<class T>  bool GetValue(std::string sName, T &Value)
    {
        std::stringstream Stream(m_mMultiMap[sName]);

        static IStreamCoder Coder;
        Coder.ItlRead(Stream, Value);
    }

   /* /// this method returns the value if it was found by reference, else the given default value
    /// the template creates an method GetValueOrDefault for each T,
    /// if a fitting GetValue(std::string, T) exists
    template<class T> bool GetValueOrDefault(std::string sName, T tDefault, T &tValue, bool bSetIfNotFound=true)
    {
        bool bFound = GetValue(sName, tValue);

        if (bFound == false)
        {
            tValue = tDefault;

            if (bSetIfNotFound)
                SetValue(sName, tDefault);
        }

        return bFound;
    };

    /// this method returns the value if it was found, else the given default value
    /// the template creates an method GetValueOrDefault for each T,
    /// if a fitting GetValue(std::string, T) exists
    template<class T> T GetValueOrDefault(std::string sName, T tDefault, bool bSetIfNotFound=true)
    {
        T tValue;
        bool bFound = GetValue(sName, tValue);

        if (bFound == false)
        {
            tValue = tDefault;

            if (bSetIfNotFound)
                SetValue(sName, tDefault);
        }

        return tValue;
    };*/



private:
    /*! \name Internal methods */
    //@{
        std::map<std::string, TMultiVar > m_mMultiMap;
    //@}
};
}


#endif
