add_library(myoi_core
        core/Ipv4Address.cpp
        core/TcpSocket.cpp
        core/FileInfo.cpp
        core/Asio.cpp)

add_library(myoi_http
        http/Http.cpp
        http/HttpRequestParser.cpp
        http/HttpRequestHandler.cpp
        )

add_executable(myoi main.cpp)
target_link_libraries(myoi myoi_core myoi_http fmt aio pthread)
