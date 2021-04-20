//
// Created by jason on 2021/4/12.
//

#ifndef NETWORK_IPV4ADDR_H
#define NETWORK_IPV4ADDR_H

#include <arpa/inet.h>

namespace network {
    class Ipv4Address {
    private:
        sockaddr_in address_{};
        char ip_[INET_ADDRSTRLEN]{""};

    public:
        Ipv4Address();

        explicit Ipv4Address(const char *ip, int port);

        explicit Ipv4Address(const sockaddr_in &socketAddress);

        ~Ipv4Address() = default;

        const char *ip() const;

        void setIp(const char *ip);

        int port() const;

        void setPort(int port);

        bool available() const;

        const sockaddr *socketAddress() const;

        static Ipv4Address HostAddress(int socketFd);

        static Ipv4Address PeerAddress(int socketFd);
    };
}
#endif //NETWORK_IPV4ADDR_H
