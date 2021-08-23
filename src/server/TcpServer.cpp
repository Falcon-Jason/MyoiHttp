//
// Created by jason on 2021/8/23.
//

#include <sys/epoll.h>

#include "server/TcpServer.h"

namespace myoi {
    TcpEvent *TcpServer::registerEvent(TcpSocket socket, Event::Mode mode) {
        mutex_.lock();

        auto newEvent = std::make_unique<TcpEvent>(socket, static_cast<EventLoop *>(this), mode);
        auto *pEvent = newEvent.get();
        EventLoop::registerEvent(newEvent.get());

        events_[socket.index()] = std::move(newEvent);
        mutex_.unlock();
        return pEvent;
    }

    void TcpServer::removeEvent(TcpEvent *event) {
        mutex_.lock();
        fmt::print(stderr, "[INFO] Connection {} from {} closed\n",
                   event->socket().index(),
                   event->socket().peerAddress().toString());

        EventLoop::removeEvent(event);

        event->parent_ = nullptr;
        mutex_.unlock();
    }

    void TcpServer::resetEvent(TcpEvent *event) {
        if (event->parent_ == nullptr && events_.count((event->nativeHandle()))) {
            events_.erase(event->nativeHandle());
        } else {
            EventLoop::resetEvent(event);
        }
    }


    void TcpServer::onAccept(Event *event) {
        auto conn = dynamic_cast<TcpEvent *>(event);
        if (conn == nullptr) { return; }

        auto newConn = conn->socket().accept();
        if (!newConn.isOpen()) { return; }

        fmt::print(stderr, "[INFO] Connection {} from {} got\n",
                   newConn.index(),
                   newConn.peerAddress().toString());

        onAcceptable(registerEvent(newConn));

        EventLoop::resetEvent(event);
    }

    void TcpServer::onRead(Event *event) {
        auto conn = dynamic_cast<TcpEvent *>(event);
        if (conn == nullptr) { return; }

        pool_.submit(std::make_unique<Task>(
                [this, conn]() {
                    onReadable(conn);
                    resetEvent(conn);
                }));
    }

    void TcpServer::onWrite(Event *event) {
        auto conn = dynamic_cast<TcpEvent *>(event);
        if (conn == nullptr) { return; }

        pool_.submit(std::make_unique<Task>(
                [this, conn]() {
                    onWritable(conn);
                    resetEvent(conn);
                }));
    }

    int TcpServer::start() {
        fmt::print(stderr, "[INFO] TcpServer Started\n");

        if (!EventLoop::open()) { return EXIT_FAILURE; }

        TcpSocket socket{};
        bool success = socket.listen(address_);
        if (!success) {
            fmt::print(stderr, "[ERROR] failed to listen to {}\n", address_.toString());
            return EXIT_FAILURE;
        }

        EventLoop::setDefaultMode(EPOLLONESHOT);
        registerEvent(socket, Event::Mode::ACCEPT);

        fmt::print(stderr, "[INFO] listener {} registered at {}\n",
                   socket.index(),
                   socket.hostAddress().toString());

        int ret = EventLoop::execute();
        fmt::print(stderr, "[INFO] TcpServer Stopped\n");
        return ret;
    }
}