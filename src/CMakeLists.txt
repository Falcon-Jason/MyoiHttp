add_library(myoi_event
        event/EpollSelector.cpp
        event/EventReactor.cpp)

add_library(myoi_util
        util/TcpSocket.cpp
        util/FileInfo.cpp
        util/InetAddress.cpp
        util/FixedThreadPool.cpp)
target_link_libraries(myoi_util fmt pthread)

add_library(myoi_http
        http/HttpUtil.cpp
        http/HttpRequestParser.cpp)

add_executable(myoi_server
        server/main.cpp
        server/HttpHandler.cpp
        server/HttpProcessor.cpp
        server/HttpReactor.cpp ../include/server/HttpReactor.h server/HttpReactor.cpp ../include/server/HttpReactor.h)

target_link_libraries(myoi_server myoi_event myoi_util myoi_http fmt)

#target_link_libraries(myoi_server myoi_util fmt aio pthread)

#add_executable(myoi main.cpp)
