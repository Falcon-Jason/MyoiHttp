//
// Created by jason on 2021/4/12.
//

#ifndef NETWORK_TCPCONNECTION_H
#define NETWORK_TCPCONNECTION_H

#include "core/Ipv4Address.h"
#include <memory>

namespace myoi {
    class TcpConnection {
    private:
        Socket socket_{-1};

    public:
        TcpConnection() = default;
        ~TcpConnection() = default;

        bool connect(const Ipv4Address& address);
        bool close();

        [[nodiscard]] bool isOpen() const { return socket_ >= 0; }
        [[nodiscard]] const Socket &socket() const { return socket_; }

        bool hostAddress(Ipv4Address &address) const;
        bool peerAddress(Ipv4Address &address) const;

        ssize_t tryRead(char *buffer, size_t size) const;
        ssize_t tryWrite(const char *buffer, size_t size) const;

        friend class TcpListener;

    };
}

#endif //NETWORK_TCPCONNECTION_H
