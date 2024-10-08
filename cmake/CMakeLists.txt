cmake_minimum_required(VERSION 3.14.3)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
	message(WARNING "CMAKE_TOOLCHAIN_FILE: please specify cmake toolchain file in cmake command line.")
endif()
message(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")

# For Visual Studio Generator (not Ninja), it is unnecessary to set CMAKE_MAKE_PROGRAM.
if (NOT ${CMAKE_GENERATOR} MATCHES "Visual Studio")
	if(NOT DEFINED CMAKE_MAKE_PROGRAM)
		message(WARNING "CMAKE_MAKE_PROGRAM: please specify make program in cmake command line.")
	endif()

	message(STATUS "CMAKE_MAKE_PROGRAM: ${CMAKE_MAKE_PROGRAM}")
endif()

project(AlgorithmZoo C CXX)

option(BUILD_FACE_SDK "Build Face SDK" OFF)
option(BUILD_MATIERIAL_OCR_SDK "Build matierial ocr SDK" OFF)
option(BUILD_SAFE_PRODUCTION_SDK "Build safe production SDK" OFF)
option(BUILD_GENERAL_CV_SDK "Build general cv SDK" OFF)
option(BUILD_MODULE_FRAME_GEN "Build new module frame generator." OFF)
option(BUILD_TEST_MODEL "Build test model." OFF)
option(COSINE_DISTANCE "Use cosine distance in irsiviel." ON)
option(USE_OPENMP "Use OpenMP" OFF)
option(BUILD_DEBUG_INFO "Build debug info." OFF)
option(BUILD_RV1106 "Build for RV1106." OFF)

set(RKNNAPI_VERSION NONE CACHE STRING "Choose RKNNAPI_VERSION instead of Excalibur")
set_property(CACHE RKNNAPI_VERSION PROPERTY STRINGS NONE 1 2)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(CMAKE_FIND_LIBRARY_PREFIXES "lib")
endif()

list(APPEND COMMON_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../cpp/common/include ${CMAKE_CURRENT_SOURCE_DIR}/../cpp/common/include/Primitives)

if(NOT DEFINED COMMON_LIBRARY_DIRS)
	message(FATAL_ERROR "COMMON_LIBRARY_DIRS NOT DEFINED: You must specify common library's directories.")
endif()

# list(APPEND COMMON_LIBRARIES_NAMES primitives julius)

if(RKNNAPI_VERSION STREQUAL "1")
	list(APPEND COMMON_LIBRARIES_NAMES rknn_api)
	add_definitions(-DUSE_RKNNAPI)
elseif(RKNNAPI_VERSION STREQUAL "2")
	add_definitions(-DUSE_RKNN2API)
	if(BUILD_RV1106)
		list(APPEND COMMON_LIBRARIES_NAMES rknnmrt)
		add_definitions(-DBUILD_RV1106)
	else()
		list(APPEND COMMON_LIBRARIES_NAMES rknnrt)
	endif()
endif()
list(APPEND COMMON_LIBRARIES_NAMES excalibur)
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	foreach(library_name ${COMMON_LIBRARIES_NAMES})
		find_library(library
			NAMES ${library_name}
			PATHS ${COMMON_LIBRARY_DIRS}
			NO_DEFAULT_PATH
		)
		message(STATUS "${library_name} ${library}")
		list(APPEND COMMON_LIBRARIES ${library})
		unset(library CACHE)
	endforeach()
else()
	set(COMMON_LIBRARIES ${COMMON_LIBRARIES_NAMES})
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Android")
	message(STATUS "ANDROID_NDK: ${ANDROID_NDK}")
	message(STATUS "ANDROID_ABI: ${ANDROID_ABI}")
	message(STATUS "ANDROID_PLATFORM: ${ANDROID_PLATFORM}")
	message(STATUS "ANDROID_TOOLCHAIN: ${ANDROID_TOOLCHAIN}")
	message(STATUS "ANDROID_STL: ${ANDROID_STL}")
endif()

# if(((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")) AND (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64"))
# 	#if(HAVE_AVX2)
# 		add_compile_options(-mavx2)
# 		add_definitions(-D__AVX2__)
# 	#endif()
# 	#if(HAVE_AVX)
# 		add_compile_options(-mavx -mfma)
# 		add_definitions(-D__AVX__ -D__FMA__)
# 	#endif()
# 	#if(HAVE_SSE)
# 		add_compile_options(-mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mf16c)
# 		add_definitions(-D__SSE4_2__ -D__SSE4_1__ -D__SSSE3__ -D__SSE3__)
# 	#endif()
# endif()

if((NOT (CMAKE_BUILD_TYPE STREQUAL "Debug")) AND (NOT (CMAKE_BUILD_TYPE STREQUAL "Release")))
	set(CMAKE_BUILD_TYPE "Release")
endif()
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# if(CMAKE_SYSTEM_NAME STREQUAL "Android")
# 	add_compile_options(-frtti -fexceptions)
# endif()


#CMAKE_CXX_VISIBILITY_PRESET 如果设置隐藏的话 外部找不到接口
if((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))
	add_compile_options(-fPIC -Wall -fpermissive)
	if(CMAKE_BUILD_TYPE STREQUAL "Release")
		# set(CMAKE_CXX_VISIBILITY_PRESET hidden)
		message(STATUS "CMAKE_CXX_VISIBILITY_PRESET: ${CMAKE_CXX_VISIBILITY_PRESET}")
	endif()
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(CMAKE_IMPORT_LIBRARY_PREFIX lib)
	set(CMAKE_SHARED_LIBRARY_PREFIX lib)
	set(CMAKE_STATIC_LIBRARY_PREFIX lib)
endif()

include(Dependencies.cmake)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)


add_subdirectory(Body)
add_subdirectory(Peoplehead)
