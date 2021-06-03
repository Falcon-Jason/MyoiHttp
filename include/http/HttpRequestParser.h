//
// Created by jason on 30/5/21.
//

#ifndef DEMOS_HTTPREQUESTPARSER_H
#define DEMOS_HTTPREQUESTPARSER_H

#include "http/HttpRequest.h"
#include <string>

namespace http {
    class HttpRequestParser {
    public:
        enum class Status;

    private:
        HttpRequest request_{};
        std::string buffer_{};
        Status status_;
        decltype(request_.headers_)::iterator headerToParse;

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


#endif //DEMOS_HTTPREQUESTPARSER_H
