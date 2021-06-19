//
// Created by jason on 2021/4/12.
//

#ifndef MYOIHTTP_TCPCONNECTION_H
#define MYOIHTTP_TCPCONNECTION_H

#include "util/Ipv4Address.h"
#include <memory>

namespace myoi {

    enum class SocketType { INVALID_TYPE, LISTENER, CONNECTION};

    class TcpSocket {
    public:
    private:
        int fildes_{-1};
        SocketType type_{SocketType::INVALID_TYPE};
        TcpSocket(int socket, SocketType type) : fildes_{socket}, type_{type} {}

    public:
        TcpSocket() = default;
        ~TcpSocket() = default;

        bool connect(const Ipv4Address& address);
        bool listen(const Ipv4Address &address);
        bool close();

        [[nodiscard]] bool isOpen() const { return fildes_ >= 0; }
        [[nodiscard]] int index() const { return fildes_; }
        [[nodiscard]] SocketType type() const { return type_; }

        [[nodiscard]] Ipv4Address hostAddress() const;
        [[nodiscard]] Ipv4Address peerAddress() const;

        ssize_t tryRead(char *buffer, size_t size) const;
        ssize_t tryWrite(const char *buffer, size_t size) const;

        [[nodiscard]] TcpSocket accept() const;

        bool operator==(const TcpSocket &rhs) const { return fildes_ == rhs.fildes_; }

    };
}

#endif //MYOIHTTP_TCPCONNECTION_H
