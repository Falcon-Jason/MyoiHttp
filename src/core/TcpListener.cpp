//
// Created by jason on 2021/4/12.
//

#include "core/Error.h"
#include "core/TcpListener.h"
#include <unistd.h>
#include <arpa/inet.h>

namespace network {
    TcpListener::TcpListener(const Ipv4Address &address) : fd_{-1}, address_{address} {
        ErrorIf(!address_.available(), "TcpServer: address unavailable.\n");
        fd_ = ::socket(AF_INET, SOCK_STREAM, 0);
        ErrorIf(fd_ < 0,"TcpServer: socket error: {}.\n", strerror(errno));
        ErrorIf(::bind(fd_, address_.socketAddress(), sizeof(sockaddr_in)) != 0,
                "TcpServer: bind error: {}.\n", strerror(errno));
        ErrorIf(::listen(fd_, LISTENQ) != 0, "TcpServer: listen error: {}.\n", strerror(errno));
        address_ = Ipv4Address::HostAddress(fd_);
    }

    TcpListener::TcpListener(const char *ip, int port) : TcpListener(Ipv4Address{ip, port}) {}

    TcpListener::~TcpListener() {
        if (::close(fd_) != 0) {
            Error("TcpServer: close error: {}.\n", strerror(errno));
        }
        fd_ = -1;
    }

    int TcpListener::fd() const {
        return fd_;
    }

    const Ipv4Address & TcpListener::address() const {
        return address_;
    }

    TcpConnection *TcpListener::accept() const {
        int acceptedFd = ::accept(fd_, nullptr, nullptr);
        if (acceptedFd < 0) {
            Error("TcpServer: accept error: {}.\n", strerror(errno));
        }

        return new TcpConnection{acceptedFd};
    }
}