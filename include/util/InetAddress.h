/**
 * @file InetAddress.h
 * @author Jason Cheung
 * @date 2021.04.12
 * @brief The class encapsulated internet addresses(`sockaddr_in`).
 */

#ifndef MYOI_INETADDRESS_H
#define MYOI_INETADDRESS_H

#include <string>
#include <arpa/inet.h>

namespace myoi {
    class InetAddress : sockaddr_in {
    public:
        InetAddress();

        explicit InetAddress(const char *address, uint16_t port);

        ~InetAddress() = default;

        [[nodiscard]] std::string address() const;

        [[nodiscard]] std::string toString() const;

        [[nodiscard]] uint16_t port() const;

        [[nodiscard]]constexpr sockaddr_in *unpack() { return static_cast<sockaddr_in *>(this); }

        [[nodiscard]] constexpr const sockaddr_in *unpack() const { return static_cast<const sockaddr_in *>(this); }

        [[nodiscard]] constexpr auto size() const { return sizeof(*this); }

        bool setAddress(const char *address);

        void setPort(uint16_t port);
    };
}

#endif //MYOI_INETADDRESS_H
