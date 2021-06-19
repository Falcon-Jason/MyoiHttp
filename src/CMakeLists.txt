add_library(myoi_util
        util/TcpSocket.cpp
        util/FileInfo.cpp
        util/EpollSet.cpp
        util/Ipv4Address.cpp
        util/HttpUtil.cpp
        util/HttpRequestParser.cpp
        )
target_link_libraries(myoi_util fmt)

add_executable(myoi_server
        server/HttpServer.cpp
        server/HttpHandler.cpp
        server/HttpHandlerController.cpp
        server/main.cpp)
target_link_libraries(myoi_server myoi_util fmt aio pthread)

#add_executable(myoi main.cpp)
