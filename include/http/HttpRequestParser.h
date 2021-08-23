/**
 * @file HttpRequestParser.h
 * @author Jason Cheung
 * @date 2021.05.30
 */

#ifndef MYOI_HTTPREQUESTPARSER_H
#define MYOI_HTTPREQUESTPARSER_H

#include "HttpUtil.h"
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

        void parse(const char *string);

        [[nodiscard]] bool success() const;

        [[nodiscard]] bool failure() const;

        [[nodiscard]] bool open() const;

        HttpRequest *datum() { return success() ? &request_ : nullptr; }

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


#endif //MYOI_HTTPREQUESTPARSER_H
