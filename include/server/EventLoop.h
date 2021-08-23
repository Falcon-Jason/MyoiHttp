/**
 * @file EventReactor.h
 * @author Jason Cheung
 * @date 2021.06.21
 * @brief the definition of a basic & simple reactor.
 */

#ifndef MYOI_EVENTLOOP_H
#define MYOI_EVENTLOOP_H

#include "Event.h"
#include "EpollSelector.h"

namespace myoi {
    class EventLoop {
    private:
        EpollSelector epoll{};
        int timeout{-1};
        volatile int term{1};
        int queueSize{};

    public:
        explicit EventLoop(int queueSize) : queueSize{queueSize} {}

        virtual ~EventLoop() = default;

        bool open();

        bool close();

        int execute();

        void terminate();

        [[nodiscard]] bool isOpen() const;

        bool registerEvent(Event *event);

        bool removeEvent(Event *event);

        bool resetEvent(Event *event);

        void setDefaultMode(uint32_t mode);

        virtual void onRead(Event *event) = 0;

        virtual void onWrite(Event *event) = 0;

        virtual void onAccept(Event *event) = 0;

    private:

    };
}
#endif //MYOI_EVENTLOOP_H
