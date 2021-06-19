//
// Created by jason on 2021/4/12.
//

#include "util/TcpSocket.h"
#include "util/Ipv4Address.h"
#include <iostream>
#include <cassert>
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#include <fcntl.h>

namespace myoi {
    bool TcpSocket::close() {
        auto ret = ::close(fildes_);
        fildes_ = -1;
        return (ret == 0);
    }

    bool TcpSocket::connect(const Ipv4Address &address) {
        type_ = SocketType::CONNECTION;
        fildes_ = ::socket(AF_INET, SOCK_STREAM, 0);
        if (fildes_ < 0) { return false; }

        auto ret = ::connect(fildes_, (sockaddr *)address.unpack(), address.size());
        if (ret < 0) { close(); return false; }

        return true;
    }

    bool TcpSocket::listen(const Ipv4Address &address) {
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
        type_ = SocketType::LISTENER;
        return true;
    }

    Ipv4Address TcpSocket::hostAddress() const {
        assert(isOpen());

        Ipv4Address address{};
        socklen_t length = address.size();
        auto ret = ::getsockname(fildes_, (sockaddr *) address.unpack(), &length);
        if (ret != 0) { return Ipv4Address{}; };
        return address;
    }

    Ipv4Address TcpSocket::peerAddress() const {
        assert(isOpen());

        Ipv4Address address{};
        socklen_t length = address.size();
        auto ret = ::getpeername(fildes_, (sockaddr *) address.unpack(), &length);
        if (ret != 0) { return Ipv4Address{}; };
        return address;
    }

    ssize_t TcpSocket::tryRead(char *buffer, size_t size) const {
        assert(isOpen() && type_ == SocketType::CONNECTION);
        return ::read(fildes_, buffer, size);
    }

    ssize_t TcpSocket::tryWrite(const char *buffer, size_t size) const {
        assert(isOpen() && type_ == SocketType::CONNECTION);
        return ::write(fildes_, buffer, size);
    }

    TcpSocket TcpSocket::accept() const {
        assert(isOpen() && type_ == SocketType::LISTENER);
        TcpSocket connection{};
        connection.fildes_ = ::accept(fildes_, nullptr, nullptr);
        connection.type_ = SocketType::CONNECTION;
        return connection;
    }
}