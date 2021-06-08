//
// Created by jason on 3/6/21.
//

#ifndef MYOIHTTP_HTTPRESPONSE_H
#define MYOIHTTP_HTTPRESPONSE_H

#include "Http.h"

namespace myoi {
    class HttpResponse {
    private:
        HttpVersion version_{};
        int status_{};
        HttpHeaders headers_{};
        HttpResponse() = default;

    public:
        HttpResponse(HttpVersion version, int status, HttpHeaders headers)
            : version_{version}, status_{status}, headers_{std::move(headers)} {}

        [[nodiscard]] HttpVersion version() const { return version_; }
        [[nodiscard]] int status() const { return status_; }
        [[nodiscard]] const HttpHeaders &headers() const { return headers_; };

        friend class HttpRequestHandler;
    };
}

#endif //MYOIHTTP_HTTPRESPONSE_H
