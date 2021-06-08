//
// Created by jason on 2021/4/12.
//

#ifndef MYOIHTTP_IPV4ADDRESS_H
#define MYOIHTTP_IPV4ADDRESS_H

#include <arpa/inet.h>
#include <string_view>
#include <string>

namespace myoi {
    using Socket = int;
    class Ipv4Address : private sockaddr_in {
    private:

    public:
        Ipv4Address();

        explicit Ipv4Address(const char *address, uint16_t port);

        ~Ipv4Address() = default;

        [[nodiscard]] std::string address() const;

        [[nodiscard]] uint16_t port() const;

        [[nodiscard]]constexpr sockaddr_in *unpack() { return static_cast<sockaddr_in *>(this); }

        [[nodiscard]] constexpr const sockaddr_in *unpack() const { return static_cast<const sockaddr_in *>(this); }

        [[nodiscard]] constexpr auto size() const { return sizeof(sockaddr_in); }

        bool setAddress(const char *address);

        void setPort(uint16_t port);
    };

    bool GetHostAddress(Socket sock, Ipv4Address &address);

    bool GetPeerAddress(Socket sock, Ipv4Address &address);
}
#endif //MYOIHTTP_IPV4ADDRESS_H
