//
// Created by jason on 2021/8/23.
//

#ifndef MYOI_TCPSERVER_H
#define MYOI_TCPSERVER_H

#include "EventLoop.h"
#include "util/FixedThreadPool.h"
#include "util/InetAddress.h"
#include "server/TcpEvent.h"

#include <thread>
#include <map>
#include <mutex>
#include <functional>
#include <memory>
#include <fmt/format.h>
#include <sys/epoll.h>

namespace myoi {
    class TcpServer : private EventLoop {
    public:
        using EventSet = std::map<NativeHandle, std::unique_ptr<Event>>;

    private:
        EventSet events_{};
        std::mutex mutex_{};
        FixedThreadPool pool_;
        InetAddress address_;

    private:
        void onAccept(Event *event) override;

        void onRead(Event *event) override;

        void onWrite(Event *event) override;

    public:
        explicit TcpServer(const char *address, uint16_t port, int threadCount, int queueSize)
                : EventLoop{queueSize}, pool_{threadCount}, address_{address, port} {}

        ~TcpServer() override = default;

        int start();

        void stop() { EventLoop::terminate(); }

        TcpEvent *registerEvent(TcpSocket socket, Event::Mode mode = Event::Mode::READ);

        void removeEvent(TcpEvent *event);

        void resetEvent(TcpEvent *event);

        virtual void onAcceptable(TcpEvent *event) {};

        virtual void onReadable(TcpEvent *event) {};

        virtual void onWritable(TcpEvent *event) {};

    };
}

#endif //MYOI_TCPSERVER_H
