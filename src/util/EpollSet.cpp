//
// Created by jason on 16/6/21.
//

#include "util/EpollSet.h"
#include <sys/epoll.h>

namespace myoi {
    constexpr int EPOLL_SIZE = 64;

    static epoll_event MakeEvent(const TcpSocket &socket) {
        epoll_event event{};
        event.data.ptr = (void *)&socket;
        event.events = EPOLLIN | EPOLLONESHOT;
        return event;
    }

    bool EpollSet::init() {
        fildes_ = epoll_create(EPOLL_SIZE);
        return fildes_ >= 0;
    }

    bool EpollSet::addEvent(TcpSocket *socket) const {
        auto event = MakeEvent(*socket);
        return (epoll_ctl(fildes_, EPOLL_CTL_ADD, socket->index(), &event) == 0);
    }

    bool EpollSet::resetEvent(TcpSocket *socket) const {
        auto event = MakeEvent(*socket);
        return (epoll_ctl(fildes_, EPOLL_CTL_MOD, socket->index(), &event) == 0);
    }

    bool EpollSet::removeEvent(TcpSocket *socket) const {
        auto event = MakeEvent(*socket);
        return (epoll_ctl(fildes_, EPOLL_CTL_DEL, socket->index(), &event) == 0);
    }

    TcpSocket * EpollSet::wait(int timeout) const {
        epoll_event event{};
        int ret = epoll_wait(fildes_, &event, 1, timeout);
        if (ret != 1) { return nullptr; }
        return (TcpSocket *)event.data.ptr;
    }
}