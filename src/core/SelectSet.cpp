//
// Created by jason on 2021/4/21.
//

#include "core/Error.h"
#include "core/SelectSet.h"
#include <unistd.h>
#include <arpa/inet.h>

namespace network {
    SelectSet::SelectSet() {
        FD_ZERO(&set);
    }

    SelectSet::SelectSet(std::initializer_list<int> fds) : SelectSet{} {
        for (int i : fds) {
            add(i);
        }
    }

    void SelectSet::add(int fd) {
        FD_SET(fd, &set);
        maxFd = std::max(maxFd, fd);
    }

    bool SelectSet::contains(int fd) {
        return FD_ISSET(fd, &set);
    }

    void SelectSet::clear(int fd) {
        return FD_CLR(fd, &set);
    }

    SelectSet SelectSet::select() {
        SelectSet result;
        result.set = set;
        if (::select(maxFd + 1, &result.set, nullptr, nullptr, nullptr) < 0) {
            Error("EchoServer: select error: {}.\n", strerror(errno));
        }
        return result;
    }
}
