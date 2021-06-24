/**
 * @file Event.h
 * @author Jason Cheung
 * @date 2021.06.21
 * @brief The abstract interface of events.
 */

#ifndef MYOI_EVENT_H
#define MYOI_EVENT_H

namespace myoi {
    using NativeHandle = int;

    class EventHandler;

    class Event {
    public:
        enum class Mode {
            READ, WRITE, ACCEPT
        };

    public:
        virtual ~Event() = default;
        virtual NativeHandle nativeHandle() = 0;
        virtual EventHandler* handler() = 0;
        virtual Mode mode() = 0;
    };
}

#endif //MYOI_EVENT_H
