//
// Created by jason on 16/6/21.
//

#ifndef NETWORK_EPOLLSET_H
#define NETWORK_EPOLLSET_H


#include "TcpSocket.h"

namespace myoi {
    class EpollSet {
    private:
        int fildes_{-1};

    public:
        EpollSet() = default;

        bool init();

        bool addEvent(TcpSocket *socket) const;

        bool resetEvent(TcpSocket *socket) const;

        bool removeEvent(TcpSocket *socket) const;

        [[nodiscard]] TcpSocket *wait(int timeout = -1) const;
    };
}

#endif //NETWORK_EPOLLSET_H
