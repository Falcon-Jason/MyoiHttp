//
// Created by jason on 2021/4/12.
//

#include "core/TcpConnection.h"
#include "core/Ipv4Address.h"
#include <cassert>
#include <unistd.h>
#include <arpa/inet.h>

namespace myoi {
    bool TcpConnection::connect(const Ipv4Address &address) {
        socket_ = ::socket(AF_INET, SOCK_STREAM, 0);
        if (socket_ < 0) { return false; }

        auto ret = ::connect(socket_, (sockaddr *)address.unpack(), address.size());
        if (ret < 0) { close(); return false; }

        return true;
    }

    bool TcpConnection::close() {
        auto ret = ::close(socket_);
        socket_ = -1;
        return (ret == 0);
    }

    bool TcpConnection::hostAddress(Ipv4Address &address) const {
        socklen_t length = address.size();
        auto ret = ::getsockname(socket_, (sockaddr *) address.unpack(), &length);
        return (ret == 0);
    }
    bool TcpConnection::peerAddress(Ipv4Address &address) const {
        socklen_t length = address.size();
        auto ret = ::getpeername(socket_, (sockaddr *) address.unpack(), &length);
        return (ret == 0);
    }

    ssize_t TcpConnection::tryRead(char *buffer, size_t size) const {
        assert(isOpen());
        return ::read(socket_, buffer, size);
    }

    ssize_t TcpConnection::tryWrite(const char *buffer, size_t size) const {
        assert(isOpen());
        return ::write(socket_, buffer, size);
    }
}