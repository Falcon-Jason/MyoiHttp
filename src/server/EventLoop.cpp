/**
 * @file EventReactor.cpp
 * @author Jason Cheung
 * @date 2021.06.21
 * @brief the definition of a basic & simple reactor.
 */


#include "server/EventLoop.h"
#include <fmt/format.h>

namespace myoi {
    int EventLoop::execute() {
        fmt::print(stderr, "[INFO] EventLoop Started\n");

        if (!isOpen()) { open(); }

        while (!term) {
            Event *event = epoll.wait(timeout);
            if (event == nullptr) { continue; }

            switch (event->mode()) {
                case Event::Mode::READ:
                    onRead(event);
                    break;
                case Event::Mode::WRITE:
                    onWrite(event);
                    break;
                case Event::Mode::ACCEPT:
                    onAccept(event);
                    break;
                default:
                    return 1;
            }
        }

        close();

        fmt::print(stderr, "[INFO] EventLoop Stopped\n");
        return 0;
    }

    void EventLoop::terminate() {
        term = 1;
    }

    bool EventLoop::open() {
        term = 0;
        return epoll.open(queueSize);
    }

    bool EventLoop::close() {
        return epoll.close();

    }

    bool EventLoop::isOpen() const {
        return epoll.isOpen();
    }

    bool EventLoop::registerEvent(Event *event) {
        return epoll.registerEvent(event);
    }

    bool EventLoop::removeEvent(Event *event) {
        return epoll.removeEvent(event);
    }

    bool EventLoop::resetEvent(Event *event) {
        return epoll.resetEvent(event);
    }

    void EventLoop::setDefaultMode(uint32_t mode) {
        return epoll.setDefaultMode(mode);
    }
}