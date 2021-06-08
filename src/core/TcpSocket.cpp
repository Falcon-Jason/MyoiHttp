//
// Created by jason on 2021/4/12.
//

#include "core/TcpSocket.h"
#include "core/Ipv4Address.h"
#include <iostream>
#include <cassert>
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#include <fcntl.h>

namespace myoi {
    bool TcpSocket::close() {
        auto ret = ::close(socket_);
        socket_ = -1;
        return (ret == 0);
    }

    bool TcpSocket::connect(const Ipv4Address &address) {
        type_ = SocketType::CONNECTION;
        socket_ = ::socket(AF_INET, SOCK_STREAM, 0);
        if (socket_ < 0) { return false; }

        auto ret = ::connect(socket_, (sockaddr *)address.unpack(), address.size());
        if (ret < 0) { close(); return false; }

        return true;
    }

    bool TcpSocket::listen(const Ipv4Address &address) {
        using std::cerr, std::endl;
        socket_ = ::socket(AF_INET, SOCK_STREAM, 0);
        if (socket_ < 0) {
            cerr << "socket failed" << endl;
            return false;
        }
        int flag = fcntl(socket_, F_GETFL, 0);
        fcntl(socket_, F_SETFL, flag | O_NONBLOCK);

        auto ret = ::bind(socket_, (sockaddr *) address.unpack(), address.size());
        if (ret != 0) {
            cerr << "bind failed: " << ::strerror(errno) << endl;
            close();
            return false;
        }

        ret = ::listen(socket_, 64);
        if (ret != 0) {
            cerr << "listen failed" << endl;
            close();
            return false;
        }
        type_ = SocketType::LISTENER;
        return true;
    }

    bool TcpSocket::hostAddress(Ipv4Address &address) const {
        assert(isOpen());
        socklen_t length = address.size();
        auto ret = ::getsockname(socket_, (sockaddr *) address.unpack(), &length);
        return (ret == 0);
    }

    bool TcpSocket::peerAddress(Ipv4Address &address) const {
        assert(isOpen() && type_ == SocketType::CONNECTION);

        socklen_t length = address.size();
        auto ret = ::getpeername(socket_, (sockaddr *) address.unpack(), &length);
        return (ret == 0);
    }

    ssize_t TcpSocket::tryRead(char *buffer, size_t size) const {
        assert(isOpen() && type_ == SocketType::CONNECTION);
        return ::read(socket_, buffer, size);
    }

    ssize_t TcpSocket::tryWrite(const char *buffer, size_t size) const {
        assert(isOpen() && type_ == SocketType::CONNECTION);
        return ::write(socket_, buffer, size);
    }

    TcpSocket TcpSocket::accept() const {
        assert(isOpen() && type_ == SocketType::LISTENER);
        TcpSocket connection{};
        connection.socket_ = ::accept(socket_, nullptr, nullptr);
        connection.type_ = SocketType::CONNECTION;
        return connection;
    }
}