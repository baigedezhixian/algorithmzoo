cmake_minimum_required(VERSION 3.14.3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(cw_test C CXX)

find_package(OpenCV 4.7 REQUIRED)

include(Dependencies.cmake)

file(GLOB src  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp  )
file(GLOB head ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp  )

add_executable(cw_test ${src} ${head})

target_include_directories(cw_test PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_directories(cw_test PUBLIC ${OpenCV_LIBRARY_DIRS})
target_link_libraries(cw_test PUBLIC ${OpenCV_LIBS}  )

target_include_directories(cw_test PRIVATE ${COMMON_INCLUDE_DIRS} )
target_link_libraries(cw_test PRIVATE ${COMMON_LIBRARIES} )

target_include_directories(cw_test PRIVATE ${INCLUDE_DIR})
target_link_libraries(cw_test PRIVATE  pthread  dl)