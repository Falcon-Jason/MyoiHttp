/**
 * @file HttpEvent.h
 * @author Jason Cheung
 * @date 2021.06.25
 */

#ifndef MYOI_HTTPEVENT_H
#define MYOI_HTTPEVENT_H

#include "util/TcpSocket.h"
#include "event/Event.h"
#include "http/HttpRequestParser.h"

namespace myoi {
    class HttpHandler;

    class HttpEvent : public Event{
    private:
        HttpHandler *handler_;
        Event::Mode mode_;
        TcpSocket socket_;
        HttpRequestParser parser_;

    public:
        explicit HttpEvent(TcpSocket socket, HttpHandler *handler)
            : handler_{handler}, mode_{Event::Mode::READ}, socket_{socket}, parser_{} {}

        ~HttpEvent() override { if (socket_.isOpen()) { socket_.close(); } }

        NativeHandle nativeHandle() override { return socket_.index(); }

        Mode mode() override { return mode_; }

        void setMode(Mode mode) { mode_ = mode; }

        [[nodiscard]] TcpSocket::Type type() const { return socket_.type(); }

        EventHandler * handler() override;

        TcpSocket &socket() { return socket_; }

        HttpRequestParser &parser() { return parser_; }
    };
}


#endif //MYOI_HTTPEVENT_H
