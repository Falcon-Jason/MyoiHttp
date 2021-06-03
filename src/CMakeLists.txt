add_library(myoi_core
        core/Ipv4Address.cpp
        core/TcpConnection.cpp
        core/TcpListener.cpp)

add_library(myoi_http
        http/HttpRequest.cpp
        http/HttpRequestParser.cpp)

add_executable(myoi main.cpp)
target_link_libraries(myoi myoi_core myoi_http)
