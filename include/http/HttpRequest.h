//
// Created by jason on 28/5/21.
//

#ifndef DEMOS_HTTPREQUEST_H
#define DEMOS_HTTPREQUEST_H

#include <string>
#include <map>

namespace http {
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

    class HttpRequest {
    private:
        HttpMethod method_{};
        std::string uri_{};
        HttpVersion version_{};
        std::map<std::string, std::string> headers_{};
        HttpRequest() = default;
        void clear();

    public:
        HttpRequest(HttpMethod method, const char *uri, HttpVersion version,
                    decltype(headers_) headers = decltype(headers){})
            : method_{method}, uri_{uri}, version_{version}, headers_{std::move(headers)} {}

        [[nodiscard]] HttpMethod method() const { return method_; }
        [[nodiscard]] const char *uri() const { return uri_.c_str(); }
        [[nodiscard]] HttpVersion version() const { return version_; }
        [[nodiscard]] const decltype(headers_) &headers() const { return headers_; }

        friend class HttpRequestParser;
    };
}



#endif //DEMOS_HTTPREQUEST_H
