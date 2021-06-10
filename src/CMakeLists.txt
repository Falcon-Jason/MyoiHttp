add_library(myoi_core
        core/Ipv4Address.cpp
        core/TcpSocket.cpp
        core/FileInfo.cpp
        core/Asio.cpp)

add_library(myoi_http
        http/Http.cpp
        http/HttpRequestParser.cpp
        server/HttpRequestHandler.cpp
        )

add_executable(myoi_server
        server/HttpServer.cpp
        server/main.cpp)
target_link_libraries(myoi_server myoi_http myoi_core fmt aio pthread)

#add_executable(myoi main.cpp)
