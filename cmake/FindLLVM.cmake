option(USE_LIBCLANG_STATIC_LIBRARY "Use libclang static or shared library" ON)

set(LLVM_SEARCH_PATHS	/usr/local/include/llvm
						/usr/local/opt/llvm
						${LLVM_ROOT}
						$ENV{LLVM_ROOT}
						)

if(USE_LIBCLANG_STATIC_LIBRARY)
	set(LIBCLANG_LIBRARY_NAME "libclang${CMAKE_STATIC_LIBRARY_SUFFIX}")
else()
	set(LIBCLANG_LIBRARY_NAME "libclang${CLNAG_SHARED_LIBRARY_SUFFIX}")
endif()

#find include directory
find_path(LLVM_INCLUDE_DIR
	NAMES "clang-c/Index.h"
	PATHS ${LLVM_SEARCH_PATHS}
	PATH_SUFFIXES "include"
	)

#find library directory
find_path(LLVM_LIBRARY_DIR
	NAMES ${LIBCLANG_LIBRARY_NAME}
	PATHS ${LLVM_SEARCH_PATHS}
	PATH_SUFFIXES "bin" "lib"
	)

if(NOT LLVM_INCLUDE_DIR OR NOT LLVM_LIBRARY_DIR)
	message(SEND_ERROR "Unable to find LLVM installation."
		"Make sure that [LLVM_ROOT] is set with the installation directory in either an environment variable or through the cmake argument")
endif()

set(LIBCLANG ${LLVM_LIBRARY_DIR}/${LIBCLANG_LIBRARY_NAME})
