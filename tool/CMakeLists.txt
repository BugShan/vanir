cmake_minimum_required(VERSION 2.8)

project(vanir_tool CXX)
set(VANIR_TOOL_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(VANIR_TOOL_BUILD_DIR ${CMAKE_BINARY_DIR})

add_subdirectory(${VANIR_TOOL_ROOT_DIR}/.. libvanir)
set(CMAKE_MODULE_PATH "${VANIR_TOOL_ROOT_DIR}/../cmake")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_NO_SYSTEM_PATHS ON)
set(Boost_ALL_NO_LIB ON)

# disable auto-linking
add_definitions(-DBOOST_ALL_NO_LIB)
find_package(Boost REQUIRED
	COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRES})

find_package(LLVM REQUIRED)
include_directories(${LLVM_INCLUDE_DIR})

include_directories(${VANIR_TOOL_ROOT_DIR} ${VANIR_INCLUDE_DEPS})

#include file group
file(GLOB_RECURSE VANIR_TOOL_INCLUDE_GROUP ${VANIR_TOOL_ROOT_DIR}/*.h)
foreach(inc ${VANIR_TOOL_INCLUDE_GROUP})
	string(REGEX REPLACE "(.*)/.*h$" "\\1" inc_group ${inc})
	string(REPLACE ${VANIR_TOOL_ROOT_DIR} "Header Files" inc_group ${inc_group})
	string(REPLACE "/" "\\" inc_group ${inc_group})
	source_group(${inc_group} FILES ${inc})
endforeach()

#source file group
file(GLOB_RECURSE VANIR_TOOL_SOURCES_GROUP ${VANIR_TOOL_ROOT_DIR}/*.cpp)
foreach(src ${VANIR_SOURCES_GROUP})
	string(REGEX REPLACE "(.*)/.*(c$|cpp$|cxx$|m$|mm$)" "\\1" src_group ${src})
	string(REPLACE ${VANIR_TOOL_ROOT_DIR} "Source Files" src_group ${src_group})
	string(REPLACE "/" "\\" src_group ${src_group})
	source_group(${src_group} FILES ${src})
endforeach()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(vanir ${VANIR_TOOL_INCLUDE_GROUP} ${VANIR_TOOL_SOURCES_GROUP})
target_link_libraries(vanir ${Boost_LIBRARIES} ${LIBCLANG})
