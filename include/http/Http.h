//
// Created by jason on 3/6/21.
//

#ifndef MYOIHTTP_HTTP_H
#define MYOIHTTP_HTTP_H

#include <map>
#include <string>

namespace myoi {
    using HttpHeaders = std::map<std::string, std::string>;

    enum class HttpVersion {
        HTTP_0_9,
        HTTP_1_0,
        HTTP_1_1
    };

    const char *ToString(HttpVersion version);
    bool FromString(const char *string, HttpVersion &version);

    enum class HttpMethod {
        GET,
        POST,
        HEAD
    };

    const char *ToString(HttpMethod method);
    bool FromString(const char *string, HttpMethod &method);

}

#endif //MYOIHTTP_HTTP_H
