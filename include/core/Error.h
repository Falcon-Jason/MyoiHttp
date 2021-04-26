//
// Created by jason on 2021/4/12.
//

#ifndef NETWORK_CORE_H
#define NETWORK_CORE_H

#include <bits/stdc++.h>
#include <fmt/format.h>

namespace network {
    template <class ...T>
    [[noreturn]] void Error(const char* format, T ...t)  {
        fmt::print(stderr, format, t...);
        ::exit(EXIT_FAILURE);
    }

    template <class ...T>
    void ErrorIf(bool cond, const char *format, T ...t) {
        if (cond) {
            Error(format, t...);
        }
    }
}
#endif //NETWORK_CORE_H
