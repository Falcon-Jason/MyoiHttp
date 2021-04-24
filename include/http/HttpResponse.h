//
// Created by jason on 24/4/21.
//

#ifndef NETWORK_HTTPRESPONSE_H
#define NETWORK_HTTPRESPONSE_H

#include <string>
#include <map>
#include "core/BufferedIo.h"
#include <fmt/format.h>
namespace network {
    struct HttpResponse {
        std::string status{};
        std::string version{};
        std::map<std::string, std::string> headers{};
        std::string body{};

        HttpResponse() = default;
        void parse(BufferedIo &in);
        void toString(std::string &result);
        void clear();
        void error(int status);

        template <class ...T> void append(const char *format, T ...t) {
            body.append(fmt::format(format, t...));
        }
    };
}

#endif //NETWORK_HTTPRESPONSE_H
