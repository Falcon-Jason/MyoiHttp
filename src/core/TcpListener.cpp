//
// Created by jason on 2021/4/12.
//

#include "core/TcpListener.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include <cerrno>
#include <cstring>

namespace myoi {
    using std::cerr, std::endl;

    bool TcpListener::listen(const Ipv4Address &address) {
        socket_ = ::socket(AF_INET, SOCK_STREAM, 0);
        if (socket_ < 0) {
            cerr << "socket failed" << endl;
            return false;
        }

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

        hostAddress_ = std::make_unique<Ipv4Address>(address);
        return true;
    }

    bool TcpListener::close() {
        auto ret = ::close(socket_);
        socket_ = -1;
        return (ret == 0);
    }

    const Ipv4Address & TcpListener::hostAddress() const {
        return *hostAddress_;
    }

    TcpConnection TcpListener::accept() const {
        TcpConnection connection{};
        connection.socket_ = ::accept(socket_, nullptr, nullptr);
        if (connection.socket_ < 0) {
            connection.close();
        }
        return connection;
    }
}