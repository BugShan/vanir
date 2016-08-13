cmake_minimum_required(VERSION 2.8)

project(vanir)

include_directories(include)
include_directories(/usr/local/opt/llvm/include)
include_directories(/usr/local/include)
include_directories(the3rd/bugshan/include)
include_directories(tool)
file(GLOB_RECURSE SRC tool/*.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g3")
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -L/usr/local/opt/llvm/lib -lclang -L/usr/local/lib -lboost_program_options")
add_executable(vanir ${SRC})
