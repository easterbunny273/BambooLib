cmake_minimum_required(VERSION 2.8.11)

project (BambooLib)

set(INCLUDE_DIR "include")
file (GLOB HEADER_FILES "${INCLUDE_DIR}/*.h")

source_group("Include Files" FILES ${HEADER_FILES})

add_library(BAMBOOLIB STATIC ${HEADER_FILES})
set_target_properties(BAMBOOLIB PROPERTIES LINKER_LANGUAGE CXX)

# Make sure we get C++11

SET(ENABLE_CXX11 "-std=c++1y")
if(CMAKE_COMPILER_IS_GNUCXX)
   EXECUTE_PROCESS(COMMAND "${CMAKE_CXX_COMPILER} -dumpversion" OUTPUT_VARIABLE GCC_VERSION)
   if (GCC_VERSION VERSION_LESS 4.7)
      SET(ENABLE_CXX11 "-std=c++0x")
   endif()
endif()
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ENABLE_CXX11}")




# include test subdirectory
add_subdirectory("test")

# add tests to cmake project, so that it generates a ctest target
enable_testing()
add_test(tests test/tests)

target_include_directories (tests PUBLIC include/)