//
// Created by jason on 2021/4/12.
//

#ifndef NETWORK_TCPLISTENER_H
#define NETWORK_TCPLISTENER_H

//#include "MyoiHttp.h"
#include "Ipv4Address.h"
#include "TcpConnection.h"

namespace network {
    class TcpListener {
    private:
        int fd_;
        Ipv4Address address_;
        static constexpr int LISTENQ = 1024;

    public:
        explicit TcpListener(const Ipv4Address &address);

        explicit TcpListener(const char *ip, int port);

        ~TcpListener();

        int fd() const;

        const Ipv4Address &address() const;

        TcpConnection *accept() const;
    };
}

#endif //NETWORK_TCPLISTENER_H
