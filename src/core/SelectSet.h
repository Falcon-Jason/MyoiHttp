//
// Created by jason on 2021/4/21.
//

#ifndef MYOI_SELECTSET_H
#define MYOI_SELECTSET_H

#include <unistd.h>
#include <arpa/inet.h>
#include <initializer_list>
#include <vector>

namespace myoi {
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

        bool select(SelectSet &result);
    };
}

#endif //MYOI_SELECTSET_H
