//
// Created by jason on 2021/4/12.
//

#ifndef NETWORK_TCPSERVER_H
#define NETWORK_TCPSERVER_H

//#include "MyoiHttp.h"
#include "Ipv4Address.h"
#include "TcpConnection.h"

namespace network {
    class TcpServer {
    private:
        int fd_;
        Ipv4Address address_;
        static constexpr int LISTENQ = 1024;

    public:
        explicit TcpServer(const Ipv4Address &address);

        explicit TcpServer(const char *ip, int port);

        ~TcpServer();

        int fd() const;

        TcpConnection *accept() const;
    };
}

#endif //NETWORK_TCPSERVER_H
