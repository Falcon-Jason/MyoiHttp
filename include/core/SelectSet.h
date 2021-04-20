//
// Created by jason on 2021/4/21.
//

#ifndef NETWORK_SELECTSET_H
#define NETWORK_SELECTSET_H

#include <unistd.h>
#include <arpa/inet.h>
#include <initializer_list>
#include <vector>

namespace network {
    class SelectSet {
    private:
        fd_set set{};
        int maxFd{0};

    public:
        SelectSet();

        SelectSet(std::initializer_list<int> fds);

        void add(int fd);

        bool contains(int fd);

        void clear(int fd);

        SelectSet select();
    };
}

#endif //NETWORK_SELECTSET_H
