/**
 * @file EventReactor.h
 * @author Jason Cheung
 * @date 2021.06.21
 * @brief the definition of a basic & simple reactor.
 */

#ifndef MYOI_EVENTREACTOR_H
#define MYOI_EVENTREACTOR_H

#include "event/Event.h"
#include "event/EventHandler.h"
#include "event/EpollSelector.h"

namespace myoi {
    class EventReactor {
    private:
        EpollSelector epoll{};
        int timeout{-1};
        volatile int terminate{1};

    public:
        explicit EventReactor() = default;

        bool open(int queueSize);

        int exec();

        void term();

        bool close();

        [[nodiscard]] bool isOpen() const;

        bool registerEvent(Event *event) const;

        bool removeEvent(Event *event) const;

        bool resetEvent(Event *event) const;

        void setDefaultMode(uint32_t mode);
    };
}
#endif //MYOI_EVENTREACTOR_H
