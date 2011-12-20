#ifndef ISTREAMABLE_H
#define ISTREAMABLE_H

#include "IStreamCoder.h"

#include <istream>
#include <ostream>
#include <fstream>

#include <memory>

namespace BambooLib
{

  class IStreamable
  {
  public:
    void WriteToStream(std::ostream &rOutputStream) { ItlCode(rOutputStream); }
    void ReadFromStream(std::istream &rInputStream) { ItlCode(rInputStream); }

    void WriteToFile(std::string sFilename) { std::ofstream file(sFilename); WriteToStream(file); }
    void RestoreFromFile(std::string sFilename) { std::ifstream file(sFilename); ReadFromStream(file); }

  private:
    virtual void ItlCode(std::ios &rStream) = 0;
  };

  class StreamableTest : public IStreamable
  {
  public:
    float m_fTest1;
    double m_dTest2;
    std::string m_sTest3;

  private:
    virtual void ItlCode(std::ios &rStream)
    {
      std::unique_ptr<IStreamCoder> spCoder(new IStreamCoder());

      spCoder->Code(rStream, m_fTest1);
      spCoder->Code(rStream, m_dTest2);
      spCoder->Code(rStream, m_sTest3);
    }



  };
}

#endif // ISTREAMABLE_H
