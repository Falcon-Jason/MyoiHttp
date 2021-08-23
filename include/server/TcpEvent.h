/**
 * @file HttpEvent.h
 * @author Jason Cheung
 * @date 2021.06.25
 */

#ifndef MYOI_TCPEVENT_H
#define MYOI_TCPEVENT_H

#include "util/TcpSocket.h"
#include "Event.h"
#include "http/HttpRequestParser.h"

#include <any>

namespace myoi {
    class HttpHandler;

    class TcpEvent : public Event {
    private:
        EventLoop *parent_;
        Event::Mode mode_;
        TcpSocket socket_;
        std::any context_;

    public:
        explicit TcpEvent(TcpSocket socket, EventLoop *parent, Event::Mode initialMode = Event::Mode::READ)
                : parent_{parent}, mode_{initialMode}, socket_{socket} {}

        ~TcpEvent() override { if (socket_.isOpen()) { socket_.close(); }}

        NativeHandle nativeHandle() override { return socket_.index(); }

        Mode mode() override { return mode_; }

        void setMode(Mode mode) { mode_ = mode; }

        [[nodiscard]] TcpSocket::Type type() const { return socket_.type(); }

        EventLoop *parentLoop() override { return parent_; }

        TcpSocket &socket() { return socket_; }

        [[nodiscard]] std::any &context() { return context_; }

        [[nodiscard]] const std::any &context() const { return context_; }

        friend class TcpServer;
    };
}


#endif //MYOI_TCPEVENT_H
