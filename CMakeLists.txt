cmake_minimum_required(VERSION 2.8)

project(vanir CXX)

set(LIBVANIR libvanir)

set(VANIR_ROOT_DIR	${CMAKE_CURRENT_SOURCE_DIR})
set(VANIR_BUILD_DIR	${CMAKE_BINARY_DIR})

set(VANIR_INCLUDE_DEPS ${VANIR_ROOT_DIR}/include)
include_directories(${VANIR_INCLUDE_DEPS})

#include file group
file(GLOB_RECURSE VANIR_INCLUDE_GROUP ${VANIR_ROOT_DIR}/include/*.h)
foreach(inc ${VANIR_INCLUDE_GROUP})
	string(REGEX REPLACE "(.*)/.*h$" "\\1" inc_group ${inc})
	string(REPLACE ${VANIR_ROOT_DIR}/include "Header Files" inc_group ${inc_group})
	string(REPLACE "/" "\\" inc_group ${inc_group})
	source_group(${inc_group} FILES ${inc})
endforeach()

#source file group
file(GLOB_RECURSE VANIR_SOURCES_GROUP ${VANIR_ROOT_DIR}/source/*.cpp)
foreach(src ${VANIR_SOURCES_GROUP})
	string(REGEX REPLACE "(.*)/.*(c$|cpp$|cxx$|m$|mm$)" "\\1" src_group ${src})
	string(REPLACE ${VANIR_ROOT_DIR}/source "Source Files" src_group ${src_group})
	string(REPLACE "/" "\\" src_group ${src_group})
	source_group(${src_group} FILES ${src})
endforeach()

# cxx flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_library(${LIBVANIR}
	STATIC ${VANIR_INCLUDE_GROUP} ${VANIR_SOURCES_GROUP}
	)
