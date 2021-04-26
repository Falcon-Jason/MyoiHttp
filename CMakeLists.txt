cmake_minimum_required(VERSION 3.19)
project(Network)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
add_subdirectory(examples)
add_subdirectory(src)
add_subdirectory(test)

add_executable(MyoiHttp main.cpp)
target_link_libraries(MyoiHttp libMyoiCore)
target_link_libraries(MyoiHttp libMyoiHttp)
target_link_libraries(MyoiHttp fmt)
target_link_libraries(MyoiHttp pthread)