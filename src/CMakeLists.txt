add_library(libMyoiCore
        core/Ipv4Address.cpp
        core/TcpConnection.cpp
        core/TcpListener.cpp
        core/BufferedIo.cpp
        core/SelectSet.cpp)

add_library(libMyoiHttp
        http/HttpRequest.cpp
        http/HttpResponse.cpp
        http/HttpParser.cpp
        http/HttpGenerator.cpp
        http/HttpServer.cpp)

target_link_libraries(libMyoiHttp libMyoiCore)