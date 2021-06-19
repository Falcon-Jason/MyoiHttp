//
// Created by jason on 16/6/21.
//

#ifndef NETWORK_LOGSERVER_H
#define NETWORK_LOGSERVER_H

#include <fmt/format.h>

class LogServer {
private:
    FILE *file{nullptr};

public:
    explicit LogServer(FILE *log) : file{log} {}

    template <class ...T>
    void info(T ...t) {
        return fmt::print(file, "[INFO] {}\n", fmt::format(t...));
    }

    template <class ...T>
    void error(T ...t) {
        return fmt::print(file, "[ERROR] {}\n", fmt::format(t...));
    }
};


#endif //NETWORK_LOGSERVER_H
