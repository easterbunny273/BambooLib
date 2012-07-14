#ifndef ISTREAMCODER_H
#define ISTREAMCODER_H

#include <istream>
#include <ostream>
#include <string>
#include <vector>
#include <assert.h>

namespace BambooLib
{
  class IStreamCoder
  {
  public:
    template <class T> void ItlWrite(std::ostream &rOutputStream, std::vector<T> &refVar)
      {
        size_t iLength = refVar.size();
        rOutputStream.write(reinterpret_cast<const char *>(&iLength), sizeof(iLength));

        for (unsigned int i=0; i < iLength; i++)
            ItlWrite(rOutputStream, refVar[i]);
      }

      template <class T> void ItlRead(std::istream &rInputStream, std::vector<T> &refVar)
      {
          size_t iLength;
          rInputStream.read(reinterpret_cast<char *>(&iLength), sizeof(iLength));

          refVar.resize(iLength);

          for (unsigned int i=0; i < iLength; i++)
              ItlRead(rInputStream, refVar[i]);
      }

    void ItlWrite(std::ostream &rOutputStream, std::string &refVar)
    {
      size_t iLength = refVar.size();
      rOutputStream.write(reinterpret_cast<const char *>(&iLength), sizeof(iLength));
      rOutputStream.write(reinterpret_cast<const char *>(refVar.c_str()), iLength);
    }

    void ItlRead(std::istream &rInputStream, std::string &refVar)
    {
      size_t iLength;
      rInputStream.read(reinterpret_cast<char *>(&iLength), sizeof(iLength));

      char *szBuffer = new char[iLength+1];
      rInputStream.read(szBuffer, iLength);
      szBuffer[iLength] = '\0';

      refVar = std::string(szBuffer);

      delete[] szBuffer;
    }

    template <class T> void ItlWrite(std::ostream &rOutputStream, T &refVar)
    {
      rOutputStream.write(reinterpret_cast<const char *>(&refVar), sizeof(T));
    }

    template <class T> void ItlRead(std::istream &rInputStream, T &refVar)
    {
      rInputStream.read(reinterpret_cast<char *>(&refVar), sizeof(T));
    }

    template <class T> void Code(std::ios &rStream, T &refVar)
    {
      std::ostream *oStream = dynamic_cast<std::ostream *>(&rStream);
      std::istream *iStream = dynamic_cast<std::istream *>(&rStream);

      assert (!(oStream != NULL && iStream != NULL));
      assert (!(oStream == NULL && iStream == NULL));

      if (oStream)
        ItlWrite(*oStream, refVar);
      else if (iStream)
        ItlRead(*iStream, refVar);
    }

  };

}
#endif // ISTREAMCODER_H
