//
// Created by jason on 2021/4/12.
//

#include "core/TcpServer.h"
#include "core/Network.h"


namespace network {
    TcpServer::TcpServer(const Ipv4Address &address) : fd_{-1}, address_{address} {
        ErrorIf(!address_.available(), "TcpServer: address unavailable.\n");
        fd_ = ::socket(AF_INET, SOCK_STREAM, 0);
        ErrorIf(fd_ < 0,"TcpServer: socket error: %s.\n", strerror(errno));
        ErrorIf(::bind(fd_, address_.socketAddress(), sizeof(sockaddr_in)) != 0,
                "TcpServer: bind error: %s.\n", strerror(errno));
        ErrorIf(::listen(fd_, LISTENQ) != 0, "TcpServer: listen error: %s.\n", strerror(errno));
    }

    TcpServer::TcpServer(const char *ip, int port) : TcpServer(Ipv4Address{ip, port}) {}

    TcpServer::~TcpServer() {
        if (::close(fd_) != 0) {
            Error("TcpServer: close error: %s.\n", strerror(errno));
        }
        fd_ = -1;
    }

    int TcpServer::fd() const {
        return fd_;
    }

    TcpConnection *TcpServer::accept() const {
        int acceptedFd = ::accept(fd_, nullptr, nullptr);
        if (acceptedFd < 0) {
            Error("TcpServer: accept error: %s.\n", strerror(errno));
        }

        return new TcpConnection{acceptedFd};
    }
}