#include <iostream>

using namespace std;


#include <ostream>
#include <istream>
#include <sstream>
#include <fstream>
#include <memory>

#include "assert.h"

#include "IStreamable.h"

int main()
{
  /*BambooLib::StreamableTest test;
  test.m_fTest1 = 99.9f;
  test.m_dTest2 = 1337.00001337;
  test.m_sTest3 = std::string("hallo!");

  test.WriteToFile("test2.txt");*/


  BambooLib::StreamableTest test2;

  test2.RestoreFromFile("test2.txt");

  cout << test2.m_dTest2 << ":" << test2.m_fTest1 << ":" << test2.m_sTest3 << endl;

  return 0;
}

