/**
 * @file InetAddress.cpp
 * @author Jason Cheung
 * @date 2021.04.12
 * @brief The class encapsulated internet addresses(`sockaddr_in`).
 */

#include "util/InetAddress.h"

#include <cstring>

#include <fmt/format.h>

namespace myoi {
    InetAddress::InetAddress() : sockaddr_in{} {
        ::memset(unpack(), 0, size()); // Initialize address_ by setting all zero.
        sin_family = AF_INET;
    }

    InetAddress::InetAddress(const char *address, uint16_t port) : InetAddress{} {
        setPort(port);
        setAddress(address);
    }


    std::string InetAddress::toString() const {
        return fmt::format("{}:{}", address(), port());
    }

    std::string InetAddress::address() const {
        char buffer[INET_ADDRSTRLEN];
        auto ret = ::inet_ntop(AF_INET, &sin_addr, buffer, INET_ADDRSTRLEN);
        return ret == nullptr ? "" : buffer;
    }

    bool InetAddress::setAddress(const char *address) {
        int ret = ::inet_pton(AF_INET, address, &sin_addr);
        return ret == 0;
    }

    uint16_t InetAddress::port() const {
        return ::ntohs(sin_port);
    }

    void InetAddress::setPort(uint16_t port) {
        sin_port = htons(port);
    }
}
