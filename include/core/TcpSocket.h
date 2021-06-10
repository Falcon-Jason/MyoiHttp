//
// Created by jason on 2021/4/12.
//

#ifndef MYOIHTTP_TCPCONNECTION_H
#define MYOIHTTP_TCPCONNECTION_H

#include "core/Ipv4Address.h"
#include <memory>

namespace myoi {

    enum class SocketType { INVALID_TYPE, LISTENER, CONNECTION};

    class TcpSocket {
    public:
    private:
        Socket socket_{-1};
        SocketType type_{SocketType::INVALID_TYPE};
        TcpSocket(Socket socket, SocketType type) : socket_{socket}, type_{type} {}

    public:
        TcpSocket() = default;
        ~TcpSocket() = default;

        bool connect(const Ipv4Address& address);
        bool listen(const Ipv4Address &address);
        bool close();

        [[nodiscard]] bool isOpen() const { return socket_ >= 0; }
        [[nodiscard]] int index() const { return socket_; }

        bool hostAddress(Ipv4Address &address) const;
        bool peerAddress(Ipv4Address &address) const;

        ssize_t tryRead(char *buffer, size_t size) const;
        ssize_t tryWrite(const char *buffer, size_t size) const;

        [[nodiscard]] TcpSocket accept() const;

        friend class Asio;
        friend class AsioBlock;

    };
}

#endif //MYOIHTTP_TCPCONNECTION_H
