//
// Created by jason on 2021/4/12.
//

#ifndef NETWORK_NETWORK_H
#define NETWORK_NETWORK_H

#include <bits/stdc++.h>
#include <unistd.h>
#include <arpa/inet.h>

namespace network {
    template <class ...T>
    [[noreturn]] void Error(const char* format, T ...t)  {
        ::fprintf(stderr, format, t...);
        ::exit(EXIT_FAILURE);
    }

    template <class ...T>
    void ErrorIf(bool cond, const char *format, T ...t) {
        if (cond) {
            Error(format, t...);
        }
    }
}
#endif //NETWORK_NETWORK_H
