//
// Created by jason on 28/5/21.
//

#ifndef MYOIHTTP_HTTPREQUEST_H
#define MYOIHTTP_HTTPREQUEST_H

#include "Http.h"
#include <string>
#include <map>

namespace myoi {
    class HttpRequest {
    private:
        HttpMethod method_{};
        std::string uri_{};
        HttpVersion version_{};
        HttpHeaders headers_{};
        HttpRequest() = default;
        void clear() {
            uri_.clear();
            headers_.clear();
        }

    public:
        HttpRequest(HttpMethod method, const char *uri, HttpVersion version,
                    decltype(headers_) headers = decltype(headers){})
            : method_{method}, uri_{uri}, version_{version}, headers_{std::move(headers)} {}

        [[nodiscard]] HttpMethod method() const { return method_; }
        [[nodiscard]] const char *uri() const { return uri_.c_str(); }
        [[nodiscard]] HttpVersion version() const { return version_; }
        [[nodiscard]] const HttpHeaders &headers() const { return headers_; }

        friend class HttpRequestParser;
    };
}



#endif //MYOIHTTP_HTTPREQUEST_H
