cmake_minimum_required(VERSION 2.8.11)

project (BambooLib)

set(INCLUDE_DIR "include")
file (GLOB HEADER_FILES "${INCLUDE_DIR}/*.h")

aux_source_directory(src SOURCE_FILES)

add_definitions(-DBAMBOOLIB_EXPORTS)
source_group("Include Files" FILES ${HEADER_FILES})
add_library (BambooLib SHARED ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories (BambooLib PUBLIC include/)


# Make sure we get C++11

SET(ENABLE_CXX11 "-std=c++1y")
if(CMAKE_COMPILER_IS_GNUCXX)
   EXECUTE_PROCESS(COMMAND "${CMAKE_CXX_COMPILER} -dumpversion" OUTPUT_VARIABLE GCC_VERSION)
   if (GCC_VERSION VERSION_LESS 4.7)
      SET(ENABLE_CXX11 "-std=c++0x")
   endif()
endif()
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ENABLE_CXX11}")


#if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
#   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -stdlib=libc++")
#endif()

#target_compile_features(BambooLib PUBLIC cxx_constexpr)

SET_TARGET_PROPERTIES(BambooLib PROPERTIES DEBUG_POSTFIX "_d")

add_custom_command(TARGET BambooLib POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory $<TARGET_FILE_DIR:BambooLib> ${CMAKE_SOURCE_DIR}/lib)

# include test subdirectory
add_subdirectory("test")

# add tests to cmake project, so that it generates a ctest target
enable_testing()
add_test(tests test/tests)