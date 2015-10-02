cmake_minimum_required(VERSION 2.8.11)

project (BambooLib)

set(INCLUDE_DIR "include")
file (GLOB HEADER_FILES "${INCLUDE_DIR}/*.h")

aux_source_directory(src SOURCE_FILES)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -W4")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -W4")

 
add_definitions(-DBAMBOOLIB_EXPORTS)
source_group("Include Files" FILES ${HEADER_FILES})
add_library (BambooLib SHARED ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories (BambooLib PUBLIC include/)


# Make sure we get C++11
if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall")
endif()
#target_compile_features(BambooLib PUBLIC cxx_constexpr)

SET_TARGET_PROPERTIES(BambooLib PROPERTIES DEBUG_POSTFIX "_d")

add_custom_command(TARGET BambooLib POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory $<TARGET_FILE_DIR:BambooLib> ${CMAKE_SOURCE_DIR}/lib)

# include test subdirectory
add_subdirectory("test")

# add tests to cmake project, so that it generates a ctest target
enable_testing()
add_test(tests test/tests)