//
// Created by jason on 2021/4/12.
//

#ifndef NETWORK_TCPCONNECTION_H
#define NETWORK_TCPCONNECTION_H

#include "core/BufferedIo.h"
#include "core/Ipv4Address.h"
#include "core/Error.h"
#include <memory>

namespace network {
    class TcpConnection {
    private:
        Ipv4Address hostAddress_;
        Ipv4Address peerAddress_;
        std::unique_ptr<BufferedIo> io_;

        explicit TcpConnection(int fd);

    public:
        explicit TcpConnection(const char *address, int port);

        ~TcpConnection() = default;

        const Ipv4Address &hostAddress() const;

        const Ipv4Address &peerAddress() const;

        BufferedIo &io();

        int fd() const;

        friend class TcpListener;
    };
}

#endif //NETWORK_TCPCONNECTION_H
