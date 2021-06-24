/**
 * @file EventHandler.h
 * @author Jason Cheung
 * @date 2021.06.21
 * @brief the abstract interface of event handlers.
 */

#ifndef MYOI_EVENTHANDLER_H
#define MYOI_EVENTHANDLER_H

#include "event/Event.h"
#include <functional>

namespace myoi {
    class EventReactor;

    class EventHandler {
    public:
        virtual ~EventHandler() = default;
        virtual void handle(Event *event, EventReactor *reactor) = 0;
    };
}
#endif //MYOI_EVENTHANDLER_H
