//
// Created by jason on 2021/4/21.
//

#ifndef NETWORK_HTTPREQUEST_H
#define NETWORK_HTTPREQUEST_H

#include <string>
#include <map>
#include "core/BufferedIo.h"

namespace network{
    struct HttpRequest {
        enum class Method {INVALID,GET,POST};
        static Method StringToMethod(const char *str);
        static const char * MethodToString(Method method);

        Method method{Method::INVALID};
        std::string path{};
        std::string version{};
        std::map<std::string, std::string> headers{};
        std::string content{};

        HttpRequest() = default;

        void parse(BufferedIo &in);
        std::string toString() const;
        void clear();
        void error();

    };

}

#endif //NETWORK_HTTPREQUEST_H
