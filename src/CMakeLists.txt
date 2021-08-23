
add_library(myoi_util
        util/TcpSocket.cpp
        util/FileInfo.cpp
        util/InetAddress.cpp
        util/FixedThreadPool.cpp)

target_link_libraries(myoi_util fmt pthread)

add_library(myoi_server
        server/EpollSelector.cpp
        server/EventLoop.cpp
        server/TcpServer.cpp)

add_library(myoi_http
        http/HttpUtil.cpp
        http/HttpRequestParser.cpp
        http/HttpServer.cpp
        http/HttpHandler.cpp)

add_executable(MyoiHttp http/main.cpp)

target_link_libraries(MyoiHttp myoi_http myoi_server myoi_util fmt)

add_executable(MyoiEcho echo/main.cpp)

target_link_libraries(MyoiEcho myoi_server myoi_util)

#target_link_libraries(myoi_server myoi_util fmt aio pthread)

#add_executable(myoi main.cpp)
