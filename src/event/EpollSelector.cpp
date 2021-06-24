/**
 * @file EpollSelector.cpp
 * @author Jason Cheung
 * @date 2021.06.16
 * @brief The class encapsulated multiplex IO `epoll`.
 */

#include "event/EpollSelector.h"
#include <sys/epoll.h>
#include <unistd.h>

namespace myoi {
    static epoll_event MakeEvent(Event *event, uint32_t mode) {
        epoll_event epollEvent{};
        epollEvent.data.ptr = (void *)event;
        epollEvent.events = mode;
        return epollEvent;
    }

    bool EpollSelector::open(int queueSize) {
        fildes_ = epoll_create(queueSize);
        return fildes_ >= 0;
    }

    bool EpollSelector::close() {
        int ret = ::close(fildes_);
        fildes_ = -1;
        return (ret == 0);
    }

    bool EpollSelector::registerEvent(Event *event, uint32_t mode) const {
        auto epollEvent = MakeEvent(event, defaultMode_ | mode);
        return (epoll_ctl(fildes_, EPOLL_CTL_ADD, event->nativeHandle(), &epollEvent) == 0);
    }

    bool EpollSelector::resetEvent(Event *event, uint32_t mode) const {
        auto epollEvent = MakeEvent(event, defaultMode_ | mode);
        return (epoll_ctl(fildes_, EPOLL_CTL_MOD, event->nativeHandle(), &epollEvent) == 0);
    }

    bool EpollSelector::removeEvent(Event *event, uint32_t mode) const {
        auto epollEvent = MakeEvent(event, defaultMode_ | mode);
        return (epoll_ctl(fildes_, EPOLL_CTL_DEL, event->nativeHandle(), &epollEvent) == 0);
    }

    Event *EpollSelector::wait(int timeout) const {
        epoll_event event{};
        int ret = epoll_wait(fildes_, &event, 1, timeout);
        if (ret != 1) { return nullptr; }
        return (Event *) event.data.ptr;
    }
}