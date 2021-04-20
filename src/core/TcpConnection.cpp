//
// Created by jason on 2021/4/12.
//

#include "core/TcpConnection.h"
#include "core/Ipv4Address.h"

namespace network {
    TcpConnection::TcpConnection(const char *address, int port)
            : hostAddress_{}, peerAddress_{address, port}, io_{nullptr}{
        ErrorIf(!peerAddress_.available(), "TcpConnection: address_ unavailable.\n");

        int fd = ::socket(AF_INET, SOCK_STREAM, 0);
        ErrorIf(fd<0,"TcpConnection: io_ failed: %s.\n", strerror(errno));

        ErrorIf(::connect(fd, peerAddress_.socketAddress(), sizeof(sockaddr_in)) != 0,
                "TcpConnection: connect failed: %s.\n", strerror(errno));

        io_.reset(new BufferedIo{fd});
        hostAddress_ = Ipv4Address::HostAddress(fd);
    }

    TcpConnection::TcpConnection(int fd)
        : hostAddress_{Ipv4Address::HostAddress(fd)},
          peerAddress_{Ipv4Address::PeerAddress(fd)},
          io_{new BufferedIo{fd}}{}

    const Ipv4Address &TcpConnection::peerAddress() const {
        return peerAddress_;
    }

    const Ipv4Address &TcpConnection::hostAddress() const {
        return hostAddress_;
    }

    BufferedIo &TcpConnection::io() {
        return *io_;
    }

    int TcpConnection::fd() const {
        return io_->fd();
    }
}