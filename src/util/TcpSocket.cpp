/**
 * @file TcpSocket.cpp
 * @author Jason Cheung
 * @date 2021.04.12
 * @brief The class encapsulated basic Socket APIs (read/write, connect, bind/listen, etc.).
 */

#include "util/TcpSocket.h"

#include <iostream>
#include <cassert>
#include <cerrno>
#include <cstring>

#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

namespace myoi {
    bool TcpSocket::close() {
        auto ret = ::close(fildes_);
        fildes_ = -1;
        return (ret == 0);
    }

    bool TcpSocket::connect(const InetAddress &address) {
        type_ = Type::CONNECTION;
        fildes_ = ::socket(AF_INET, SOCK_STREAM, 0);
        if (fildes_ < 0) { return false; }

        auto ret = ::connect(fildes_, (sockaddr *) address.unpack(), address.size());
        if (ret < 0) {
            close();
            return false;
        }

        return true;
    }

    bool TcpSocket::listen(const InetAddress &address) {
        using std::cerr, std::endl;
        fildes_ = ::socket(AF_INET, SOCK_STREAM, 0);
        if (fildes_ < 0) {
            cerr << "socket failed" << endl;
            return false;
        }
        int flag = fcntl(fildes_, F_GETFL, 0);
        fcntl(fildes_, F_SETFL, flag | O_NONBLOCK);

        auto ret = ::bind(fildes_, (sockaddr *) address.unpack(), address.size());
        if (ret != 0) {
            cerr << "bind failed: " << ::strerror(errno) << endl;
            close();
            return false;
        }

        ret = ::listen(fildes_, 64);
        if (ret != 0) {
            cerr << "listen failed" << endl;
            close();
            return false;
        }
        type_ = Type::LISTENER;
        return true;
    }

    InetAddress TcpSocket::hostAddress() const {
        assert(isOpen());

        InetAddress address{};
        socklen_t length = address.size();
        auto ret = ::getsockname(fildes_, (sockaddr *) address.unpack(), &length);
        if (ret != 0) { return InetAddress{}; };
        return address;
    }

    InetAddress TcpSocket::peerAddress() const {
        assert(isOpen());

        InetAddress address{};
        socklen_t length = address.size();
        auto ret = ::getpeername(fildes_, (sockaddr *) address.unpack(), &length);
        if (ret != 0) { return InetAddress{}; };
        return address;
    }

    ssize_t TcpSocket::read(char *buffer, size_t size) const {
        assert(isOpen() && type_ == Type::CONNECTION);
        return ::read(fildes_, buffer, size);
    }

    ssize_t TcpSocket::write(const char *buffer, size_t size) const {
        assert(isOpen() && type_ == Type::CONNECTION);
        return ::write(fildes_, buffer, size);
    }

    TcpSocket TcpSocket::accept() const {
        assert(isOpen() && type_ == Type::LISTENER);
        TcpSocket connection{};
        connection.fildes_ = ::accept(fildes_, nullptr, nullptr);
        connection.type_ = Type::CONNECTION;
        return connection;
    }
}