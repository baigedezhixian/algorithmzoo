# CMakeLists.txt for module1
cmake_minimum_required(VERSION 3.0)
project(body)

file(GLOB src ${CMAKE_CURRENT_SOURCE_DIR}/../../cpp/body/*.cpp)
file(GLOB header ${CMAKE_CURRENT_SOURCE_DIR}/../../cpp/body/*.hpp)

message("COMMON_LIBRAsRY_DIRsS: " ${COMMON_LIBRARY_DIRS})
message("COMMON_LIBRARIES: " ${COMMON_LIBRARIES})

add_library(body SHARED ${src} ${header} )
target_include_directories(body PUBLIC ${CMAKE_SOURCE_DIR}/../common ${COMMON_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} /home/glasssix/cw/algorithm/cpp/common)
target_link_directories(body PUBLIC ${OpenCV_LIBRARY_DIRS} ${COMMON_LIBRARY_DIRS})
target_link_libraries(body PUBLIC ${OpenCV_LIBS} ${COMMON_LIBRARIES} primitives)
