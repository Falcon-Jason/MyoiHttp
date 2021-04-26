add_executable(MyoiEchoClient echo/client.cpp)
target_link_libraries(MyoiEchoClient libMyoiCore)
target_link_libraries(MyoiEchoClient fmt)

add_executable(MyoiEchoServer echo/server.cpp)
target_link_libraries(MyoiEchoServer libMyoiCore)
target_link_libraries(MyoiEchoServer fmt)
target_link_libraries(MyoiEchoServer pthread)
