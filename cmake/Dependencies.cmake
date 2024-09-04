if((NOT DEFINED Boost_INCLUDE_DIRS) OR (Boost_INCLUDE_DIRS STREQUAL ""))
	find_package(Boost REQUIRED)
endif()

if(USE_OPENMP)
	find_package(OpenMP REQUIRED)
	add_compile_options(${OpenMP_CXX_FLAGS})
endif()

find_package(OpenCV 4.7)
if(NOT OPENCV_FOUND)
	message(WARNING "Not Found installed OpenCV, use mannual configuration.")

	if(NOT DEFINED OpenCV_INCLUDE_DIRS)
		message(FATAL_ERROR "Not define OpenCV_INCLUDE_DIRS")
	endif()

	if(NOT DEFINED OpenCV_LIBRARY_DIRS)
		message(FATAL_ERROR "Not define OpenCV_LIBRARY_DIRS")
	endif()

	if(NOT DEFINED OpenCV_LIBS)
		message(FATAL_ERROR "Not define OpenCV_LIBS")
	endif()
endif()

message(STATUS "OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
if(NOT OPENCV_FOUND)
	message(STATUS "OpenCV_LIBRARY_DIRS: ${OpenCV_LIBRARY_DIRS}")
endif()
message(STATUS "OpenCV_LIBS: ${OpenCV_LIBS}")
