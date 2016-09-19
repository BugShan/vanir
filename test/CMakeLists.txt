cmake_minimum_required(VERSION 2.8)
project(vanir_test)

set(TEST_ROOT_DIR .)

add_subdirectory(${TEST_ROOT_DIR}/../ libvanir)
set(CMAKE_MODULE_PATH "${VANIR_ROOT_DIR}/cmake")
include(VanirTool)
include(Common)

include_directories(${VANIR_INCLUDE_DEPS})
file(GLOB_RECURSE HEADER ${TEST_ROOT_DIR}/*.h)
file(GLOB_RECURSE SOURCE ${TEST_ROOT_DIR}/*.cpp)
set(SOURCE test.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(test_exe ${SOURCE} ${HEADER})
target_link_libraries(test_exe ${LIBVANIR})

vanir_parse(TARGET test_exe
			MODULE "Test"
			INPUT_LIST ${HEADER}
			OUTPUT_PATH "${CMAKE_BINARY_DIR}/Generator/output.cpp"
			TEMPLATE "${VANIR_ROOT_DIR}/mustache/VanirModuleTemplate.mustache"
			INCLUDE_DIR_LIST ${VANIR_INCLUDE_DEPS}
			OPTION"display_message"
			)
