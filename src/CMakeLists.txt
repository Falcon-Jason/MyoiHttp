add_library(MyoiHttp_Core core/Ipv4Address.cpp core/TcpConnection.cpp core/TcpListener.cpp core/BufferedIo.cpp core/SelectSet.cpp)
add_library(MyoiHttp_Http http/HttpRequest.cpp http/HttpParser.cpp http/HttpResponse.cpp)

add_executable(MyoiHttp_EchoClient echo/EchoClient.cpp)
target_link_libraries(MyoiHttp_EchoClient MyoiHttp_Core)
target_link_libraries(MyoiHttp_EchoClient fmt)

add_executable(MyoiHttp_EchoServer echo/EchoServer.cpp)
target_link_libraries(MyoiHttp_EchoServer MyoiHttp_Core)
target_link_libraries(MyoiHttp_EchoServer fmt)
target_link_libraries(MyoiHttp_EchoServer pthread)

add_executable(MyoiHttp_HttpServer http/HttpServer.cpp)
target_link_libraries(MyoiHttp_HttpServer MyoiHttp_Core)
target_link_libraries(MyoiHttp_HttpServer fmt)
target_link_libraries(MyoiHttp_HttpServer pthread)
target_link_libraries(MyoiHttp_HttpServer MyoiHttp_Http)
