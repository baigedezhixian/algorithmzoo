# CMakeLists.txt for module1
cmake_minimum_required(VERSION 3.0)
project(peoplehead)

file(GLOB src ${CMAKE_CURRENT_SOURCE_DIR}/../../cpp/peoplehead/*.cpp)
file(GLOB header ${CMAKE_CURRENT_SOURCE_DIR}/../../cpp/peoplehead/*.hpp)

message("COMMON_LIBRARY_DIRsS: " ${COMMON_LIBRARY_DIRS})
message("COMMON_LIBRARIES: " ${COMMON_LIBRARIES})

add_library(peoplehead SHARED ${src} ${header} )
target_include_directories(peoplehead PUBLIC ${CMAKE_SOURCE_DIR}/../common ${COMMON_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} /home/glasssix/cw/algorithm/cpp/common)
target_link_directories(peoplehead PUBLIC ${OpenCV_LIBRARY_DIRS} ${COMMON_LIBRARY_DIRS})
target_link_libraries(peoplehead PUBLIC ${OpenCV_LIBS} ${COMMON_LIBRARIES} )
