//
// Created by jason on 24/4/21.
//

#include "http/HttpRequest.h"
#include <fmt/format.h>

namespace network {
    HttpRequest::Method HttpRequest::StringToMethod(const char *str) {
        if (strncmp(str, "GET\0", 4) == 0) {
            return HttpRequest::Method::GET;
        } else if (strncmp(str, "POST\0", 5) == 0) {
            return HttpRequest::Method::POST;
        }
        return HttpRequest::Method::INVALID;
    }

    const char * HttpRequest::MethodToString(Method method) {
        switch (method) {
            case Method::GET:
                return "GET";
            case Method::POST:
                return "PUT";
            default:
                return "INVALID";
        }
    }

    void HttpRequest::clear() {
        method = Method::INVALID;
        path.clear();
        version.clear();
        headers.clear();
        body.clear();
    }

    void HttpRequest::error() {
        clear();
        method = Method::INVALID;
    }

    void HttpRequest::toString(std::string &result) {
        using fmt::format;
        result.clear();
        result.append(format(
                "{} {} {}\r\n",
                MethodToString(method),path,version));

        for (auto &item : headers) {
            result.append(format(
                    "{}:{}\r\n",
                    item.first, item.second));
        }

        result.append("\r\n");
        result.append(body);
    }
}