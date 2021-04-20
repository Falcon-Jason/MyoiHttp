//
// Created by jason on 2021/4/12.
//

#include "core/Ipv4Addr.h"
#include "core/Network.h"

namespace network {
    Ipv4Address::Ipv4Address() : ip_{""} {
        memset(&address_, 0, sizeof(address_)); // Initialize address_ by setting all zero.
        address_.sin_family = AF_INET;
    }

    Ipv4Address::Ipv4Address(const char *ip, int port) : Ipv4Address{} {
        setPort(port);
        setIp(ip);
    }

    Ipv4Address::Ipv4Address(const ::sockaddr_in &socketAddress) : Ipv4Address{} {
        this->address_ = socketAddress;
        const char *retCode = inet_ntop(AF_INET, &this->address_.sin_addr, ip_, INET_ADDRSTRLEN);
        if (retCode == nullptr) {
            std::strcpy(ip_, "");
        }
    }

    const char *Ipv4Address::ip() const {
        return (strcmp(ip_, "") ? ip_ : nullptr);
    }

    void Ipv4Address::setIp(const char *ip) {
        int retCode = ::inet_pton(AF_INET, ip, &address_.sin_addr);
        if (retCode > 0) {
            strncpy(ip_, ip, INET_ADDRSTRLEN);
        } else {
            strcpy(ip_, "");
        }
    }

    int Ipv4Address::port() const {
        return ::ntohs(address_.sin_port);
    }

    void Ipv4Address::setPort(int port) {
        address_.sin_port = ::htons(port);
    }

    bool Ipv4Address::available() const {
        return ip() != nullptr;
    }

    const sockaddr *Ipv4Address::socketAddress() const {
        return (sockaddr *) &address_;
    }

    Ipv4Address Ipv4Address::HostAddress(int socketFd) {
        ::sockaddr_in host{};
        ::socklen_t hostLength = sizeof(host);
        ::getsockname(socketFd, (::sockaddr *) &host, &hostLength);
        return Ipv4Address{host};
    }

    Ipv4Address Ipv4Address::PeerAddress(int socketFd) {
        ::sockaddr_in peer{};
        ::socklen_t peerLength = sizeof(peer);
        ::getpeername(socketFd, (::sockaddr *) &peer, &peerLength);
        return Ipv4Address{peer};
    }
}