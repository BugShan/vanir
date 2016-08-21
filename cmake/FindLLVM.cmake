option(USE_LIBCLANG_STATIC_LIBRARY "Use libclang static or shared library in case of both exits" ON)

set(LLVM_SEARCH_PATHS	/usr/local/include/llvm
						/usr/local/opt/llvm
						${LLVM_ROOT}
						$ENV{LLVM_ROOT}
						${VANIR_ROOT_DIR}/the3rd/llvm
						)

#find include directory
find_path(LLVM_INCLUDE_DIR
	NAMES "clang-c/Index.h"
	PATHS ${LLVM_SEARCH_PATHS}
	PATH_SUFFIXES "include"
	)

#find library directory
set(LIBCLANG_STATIC_LIBRARY_NAME "libclang${CMAKE_STATIC_LIBRARY_SUFFIX}")
find_path(LLVM_STATIC_LIBRARY_DIR
	NAMES ${LIBCLANG_STATIC_LIBRARY_NAME}
	PATHS ${LLVM_SEARCH_PATHS}
	PATH_SUFFIXES "bin" "lib"
	)
set(LIBCLANG_SHARED_LIBRARY_NAME "libclang${CMAKE_SHARED_LIBRARY_SUFFIX}")
find_path(LLVM_SHARED_LIBRARY_DIR
	NAMES ${LIBCLANG_SHARED_LIBRARY_NAME}
	PATHS ${LLVM_SEARCH_PATHS}
	PATH_SUFFIXES "bin" "lib"
	)

if(NOT LLVM_INCLUDE_DIR OR NOT (LLVM_STATIC_LIBRARY_DIR OR LLVM_SHARED_LIBRARY_DIR))
	message(SEND_ERROR "Unable to find LLVM installation."
		"Make sure that [LLVM_ROOT] is set with the installation directory in either an environment variable or through the cmake argument")
else()
	message(STATUS "LLVM: ${LLVM_INCLUDE_DIR}")
endif()

if(LLVM_STATIC_LIBRARY_DIR AND LLVM_SHARED_LIBRARY_DIR)
	if(USE_LIBCLANG_STATIC_LIBRARY)
		set(LIBCLANG ${LLVM_STATIC_LIBRARY_DIR}/${LIBCLANG_STATIC_LIBRARY_NAME})
	else()
		set(LIBCLANG ${LLVM_SHARED_LIBRARY_DIR}/${LIBCLANG_SHARED_LIBRARY_NAME})
	endif()
else()
	if(LLVM_STATIC_LIBRARY_DIR)
		set(LIBCLANG ${LLVM_STATIC_LIBRARY_DIR}/${LIBCLANG_STATIC_LIBRARY_NAME})
	else()
		set(LIBCLANG ${LLVM_SHARED_LIBRARY_DIR}/${LIBCLANG_SHARED_LIBRARY_NAME})
	endif()
endif()

