/**
 * @file HttpHandler.cpp
 * @author Jason Cheung
 * @date 2021.06.25
 */

#include "server/HttpHandler.h"
#include "server/HttpProcessor.h"

#include <thread>
#include <fmt/format.h>
#include <sys/epoll.h>

namespace myoi {
    EventHandler * HttpEvent::handler() {
        return dynamic_cast<EventHandler *>(handler_);
    }

    void HttpHandler::handle(Event *e, EventReactor *reactor) {
        auto *event = dynamic_cast<HttpEvent *>(e);
        if (event == nullptr) { return; }

        switch (event->type()) {
            case TcpSocket::Type::INVALID_TYPE:
                return;
            case TcpSocket::Type::CONNECTION:
                return process(event, reactor);
            case TcpSocket::Type::LISTENER:
                return listen(event, reactor);
        }
    }

    void HttpHandler::process(HttpEvent *event, EventReactor *reactor) {
//        auto proc = [this, event, reactor](){ HttpProcessor{this}.process(event, reactor); };
//        std::thread{proc}.detach();
//        fmt::print(stderr, "[INFO] Socket {} submitted.\n", event->socket().index());
        queueMutex_.lock();
        queue_.push_back(Task{event, reactor});
        queueMutex_.unlock();
        queueSem_.post();
    }

    void HttpHandler::listen(HttpEvent *event, EventReactor *reactor) {
        auto newConn = event->socket().accept();
        if (!newConn.isOpen()) { return; }

        fmt::print(stderr, "[INFO] Connection {} from {} got\n",
                   newConn.index(),
                   newConn.peerAddress().toString());
        registerEvent(newConn, reactor);


        reactor->resetEvent(event);
    }

    void HttpHandler::registerEvent(TcpSocket socket, EventReactor *reactor) {
        eventsMutex_.lock();

        auto newEvent = std::make_unique<HttpEvent>(socket, this);
        reactor->registerEvent(newEvent.get());

        events_[socket.index()] = std::move(newEvent);
        eventsMutex_.unlock();
    }

    void HttpHandler::removeEvent(HttpEvent *event, EventReactor *reactor) {
        eventsMutex_.lock();
        fmt::print(stderr, "[INFO] Connection {} from {} closed\n",
                   event->socket().index(),
                   event->socket().peerAddress().toString());

        reactor->removeEvent(event);

        if (events_.count(event->nativeHandle())) {
            events_.erase(event->nativeHandle());
        }
        eventsMutex_.unlock();
    }

    bool HttpHandler::init(const InetAddress &address, EventReactor *reactor) {
        TcpSocket socket{};
        bool success = socket.listen(address);
        if (!success) { return false; }

        reactor->setDefaultMode(EPOLLONESHOT);
        registerEvent(socket, reactor);

        fmt::print(stderr, "[INFO] listener {} registered at {}\n",
                   socket.index(),
                   socket.hostAddress().toString());
        return true;
    }
}
