//
// Created by jason on 2021/4/12.
//

#ifndef NETWORK_TCPLISTENER_H
#define NETWORK_TCPLISTENER_H

//#include "MyoiHttp.h"
#include "Ipv4Address.h"
#include "TcpConnection.h"

namespace myoi {
    class TcpListener {
    private:
        Socket socket_{-1};
        std::unique_ptr<Ipv4Address> hostAddress_{nullptr};

    public:
        TcpListener() = default;
        ~TcpListener() = default;

        bool listen(const Ipv4Address &address);
        bool close();

        bool isOpen() const { return socket_ >= 0; }
        Socket socket() const { return socket_; }

        const Ipv4Address &hostAddress() const;

        TcpConnection accept() const;
    };
}

#endif //NETWORK_TCPLISTENER_H
