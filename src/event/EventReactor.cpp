/**
 * @file EventReactor.cpp
 * @author Jason Cheung
 * @date 2021.06.21
 * @brief the definition of a basic & simple reactor.
 */


#include "event/EventReactor.h"
#include <cassert>
#include <sys/epoll.h>
namespace myoi {
    int EventReactor::exec() {
        assert(isOpen());

        while (!term) {
            Event *event = epoll.wait(timeout);
            if(event == nullptr) { continue; }

            event->handler()->handle(event, this);
        }

        close();
        return 0;
    }

    void EventReactor::terminate() {
        term = 1;
    }

    bool EventReactor::open(int queueSize) {
        term = 0;
        return epoll.open(queueSize);
    }

    bool EventReactor::close() {
        return epoll.close();
    }

    bool EventReactor::isOpen() const {
        return epoll.isOpen();
    }

    static uint32_t EpollMode(Event::Mode mode) {
        switch (mode) {
            case Event::Mode::READ:
            case Event::Mode::ACCEPT:
                return EPOLLIN;
            case Event::Mode::WRITE:
                return EPOLLOUT;
        }
        return 0;
    }

    bool EventReactor::registerEvent(Event *event) const {
        return epoll.registerEvent(event, EpollMode(event->mode()));
    }

    bool EventReactor::removeEvent(Event *event) const {
        return epoll.removeEvent(event, EpollMode(event->mode()));
    }

    bool EventReactor::resetEvent(Event *event) const {
        return epoll.resetEvent(event, EpollMode(event->mode()));
    }

    void EventReactor::setDefaultMode(uint32_t mode)  {
        return epoll.setDefaultMode(mode);
    }
}