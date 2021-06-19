add_library(myoi_core
        util/TcpSocket.cpp
        util/FileInfo.cpp
        util/EpollSet.cpp
        util/Ipv4Address.cpp
        )
target_link_libraries(myoi_core fmt)

add_library(myoi_http
        util/HttpUtil.cpp
        util/HttpRequestParser.cpp
        )

add_executable(myoi_server
        server/HttpServer.cpp
        server/HttpHandler.cpp
        server/HttpHandlerController.cpp
        server/main.cpp)
target_link_libraries(myoi_server myoi_http myoi_core fmt aio pthread)

#add_executable(myoi main.cpp)
