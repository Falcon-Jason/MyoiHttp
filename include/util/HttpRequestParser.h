//
// Created by jason on 30/5/21.
//

#ifndef MYOIHTTP_HTTPREQUESTPARSER_H
#define MYOIHTTP_HTTPREQUESTPARSER_H

#include "util/HttpUtil.h"
#include <string>

namespace myoi {
    class HttpRequestParser {
    public:
        enum class Status;

    private:
        HttpRequest request_{};
        std::string buffer_{};
        Status status_;
        HttpHeaders::iterator headerToParse{};

    public:
        HttpRequestParser();
        void clear();
        void parse(const char* string);

        [[nodiscard]] bool success() const;
        [[nodiscard]] bool failure() const;
        [[nodiscard]] bool open() const;

        HttpRequest &request() { return request_; }
        [[nodiscard]] const HttpRequest &request() const { return request_; }

    private:
        bool parseOne(char ch);

        bool onParsingMethod(char ch);
        bool onParsedMethod(char ch);
        bool onParsingUri(char ch);
        bool onParsedUri(char ch);
        bool onParsingVersion(char ch);
        bool onParsedVersion(char ch);
        bool onParsingHeader(char ch);
        bool onParsingHeaderName(char ch);
        bool onParsedHeaderName(char ch);
        bool onParsingHeaderValue(char ch);
        bool onParsedHeaderValue(char ch);
        bool onNeedFinalLf(char ch);

        void go(Status status);
    };
}


#endif //MYOIHTTP_HTTPREQUESTPARSER_H
