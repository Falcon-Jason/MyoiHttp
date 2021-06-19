//
// Created by jason on 2021/4/12.
//

#include "util/Ipv4Address.h"
#include <cstring>
#include <fmt/format.h>

namespace myoi {
    Ipv4Address::Ipv4Address() : sockaddr_in{} {
        ::memset(unpack(), 0, size()); // Initialize address_ by setting all zero.
        sin_family = AF_INET;
    }

    Ipv4Address::Ipv4Address(const char *address, uint16_t port) : Ipv4Address{} {
        setPort(port);
        setAddress(address);
    }


    std::string Ipv4Address::toString() const {
        return fmt::format("{}:{}", address(), port());
    }

    std::string Ipv4Address::address() const {
        char buffer[INET_ADDRSTRLEN];
        auto ret = ::inet_ntop(AF_INET, &sin_addr, buffer, INET_ADDRSTRLEN);
        return ret == nullptr ? "" : buffer;
    }

    bool Ipv4Address::setAddress(const char *address) {
        int ret = ::inet_pton(AF_INET, address, &sin_addr);
        return ret == 0;
    }

    uint16_t Ipv4Address::port() const {
        return ::ntohs(sin_port);
    }

    void Ipv4Address::setPort(uint16_t port) {
        sin_port = htons(port);
    }


}