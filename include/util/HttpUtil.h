//
// Created by jason on 3/6/21.
//

#ifndef MYOIHTTP_HTTP_H
#define MYOIHTTP_HTTP_H

#include <map>
#include <string>

namespace myoi {
    using HttpHeaders = std::map<std::string, std::string>;

    class HttpVersion {
    public:
        static HttpVersion HTTP_0_9, HTTP_1_0, HTTP_1_1;

    private:
        const char *version_;

        explicit HttpVersion(const char *version) noexcept : version_{version} {}

    public:
        [[nodiscard]] const char *toString() const { return version_; };
        static bool parse(HttpVersion& version, const char *str);
        bool operator==(HttpVersion rhs) const { return version_ == rhs.version_; }

    };

    class HttpMethod {
    public:
        static HttpMethod GET, POST, HEAD;

    private:
        const char *method_;

        explicit HttpMethod(const char *method) noexcept : method_{method} {}

    public:
        [[nodiscard]] const char *toString() const { return method_; };
        static bool parse(HttpMethod& method, const char *str);
        bool operator==(HttpMethod rhs) const { return method_ == rhs.method_; }

    };

    class HttpRequest {
    private:
        HttpMethod method_{HttpMethod::GET};
        std::string uri_{};
        HttpVersion version_{HttpVersion::HTTP_1_0};
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

    class HttpResponse {
    private:
        HttpVersion version_{HttpVersion::HTTP_1_0};
        int status_{};
        HttpHeaders headers_{};
        HttpResponse() = default;

    public:
        HttpResponse(HttpVersion version, int status, HttpHeaders headers)
                : version_{version}, status_{status}, headers_{std::move(headers)} {}

        [[nodiscard]] HttpVersion version() const { return version_; }
        [[nodiscard]] int status() const { return status_; }
        [[nodiscard]] const HttpHeaders &headers() const { return headers_; };
        [[nodiscard]] std::string toString() const;


        friend class HttpHandler;

    private:
        const static std::map<int, std::string> StatusInfo_;

    public:
        const static char *StatusInfo(int status) {
            return StatusInfo_.count(status)
                   ? StatusInfo_.at(status).c_str() : "Unknown Error";
        }
    };

}

#endif //MYOIHTTP_HTTP_H
