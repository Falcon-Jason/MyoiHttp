/**
 * @file EpollSelector.h
 * @author Jason Cheung
 * @date 2021.06.16
 * @brief The class encapsulated multiplex IO `epoll`.
 */

#ifndef MYOI_EPOLLSELECTOR_H
#define MYOI_EPOLLSELECTOR_H

#include "Event.h"
#include <cstdint>

namespace myoi {
    class EpollSelector {
    private:
        int fildes_{-1};
        uint32_t defaultMode_{0};

    public:
        explicit EpollSelector() = default;

        bool open(int queueSize);

        bool close();

        [[nodiscard]] bool isOpen() const { return fildes_ >= 0; }

        bool registerEvent(Event *event) const;

        bool removeEvent(Event *event) const;

        bool resetEvent(Event *event) const;

        void setDefaultMode(uint32_t mode) { defaultMode_ = mode; }

        [[nodiscard]] Event *wait(int timeout = -1) const;
    };
}

#endif //MYOI_EPOLLSELECTOR_H
