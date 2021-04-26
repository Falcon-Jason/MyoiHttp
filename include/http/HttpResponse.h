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
    const extern std::map<std::string, std::string> HttpStatusInfo;
    const extern std::map<std::string, std::string> ContentTypes;
    constexpr auto DEFAULT_CONTENT_TYPE = "text/plain";

    struct HttpResponse {
        std::string status{"500"};
        std::string version{"HTTP/1.0"};
        std::map<std::string, std::string> headers{
            {"Connection", "close"},
            {"Server", "Myoi Http"}};
        std::string content{};

        HttpResponse() = default;
        void parse(BufferedIo &in);
        std::string toString() const;
        void clear();
        void error(const char *status);
        void setContentFile(const char *filename);
        void refreshContentLength();
    };
}

#endif //NETWORK_HTTPRESPONSE_H
