/**
 * @file TcpSocket.h
 * @author Jason Cheung
 * @date 2021.04.12
 * @brief The class encapsulated basic Socket APIs (read/write, connect, bind/listen, etc.).
 */

#ifndef MYOI_TCPSOCKET_H
#define MYOI_TCPSOCKET_H

#include "util/InetAddress.h"

namespace myoi {


    class TcpSocket {
    public:
        enum class Type {
            INVALID_TYPE, LISTENER, CONNECTION
        };

    private:
        int fildes_{-1};
        Type type_{Type::INVALID_TYPE};

        TcpSocket(int socket, Type type) : fildes_{socket}, type_{type} {}

    public:
        TcpSocket() = default;

        ~TcpSocket() = default;

        bool connect(const InetAddress &address);

        bool listen(const InetAddress &address);

        bool close();

        [[nodiscard]] bool isOpen() const { return fildes_ >= 0; }

        [[nodiscard]] int index() const { return fildes_; }

        [[nodiscard]] Type type() const { return type_; }

        [[nodiscard]] InetAddress hostAddress() const;

        [[nodiscard]] InetAddress peerAddress() const;

        ssize_t read(char *buffer, size_t size) const;

        ssize_t write(const char *buffer, size_t size) const;

        [[nodiscard]] TcpSocket accept() const;

        bool operator==(const TcpSocket &rhs) const { return fildes_ == rhs.fildes_; }

    };
}

#endif //MYOI_TCPSOCKET_H
