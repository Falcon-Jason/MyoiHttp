//
// Created by jason on 30/5/21.
//

#include "http/HttpRequestParser.h"

namespace http {
    constexpr int BUFFER_SIZE = 4096;

    enum class HttpRequestParser::Status {
        SUCCESS,
        FAILURE,
        OPEN_PARSING_METHOD,
        OPEN_PARSED_METHOD,
        OPEN_PARSING_URI,
        OPEN_PARSED_URI,
        OPEN_PARSING_VERSION,
        OPEN_PARSED_VERSION,
        OPEN_PARSING_HEADER,
        OPEN_PARSING_HEADER_NAME,
        OPEN_PARSED_HEADER_NAME,
        OPEN_PARSING_HEADER_VALUE,
        OPEN_PARSED_HEADER_VALUE,
        OPEN_NEED_FINAL_LF
    };

    HttpRequestParser::HttpRequestParser() {
        buffer_.reserve(BUFFER_SIZE);
        status_ = Status::OPEN_PARSING_METHOD;
    }

    void HttpRequestParser::clear() {
        request_.clear();
        buffer_.clear();
        status_ = Status::OPEN_PARSING_METHOD;
    }

    bool HttpRequestParser::success() const {
        return status_ == Status::SUCCESS;
    }

    bool HttpRequestParser::failure() const {
        return status_ == Status::FAILURE;
    }

    bool HttpRequestParser::open() const {
        return status_ != Status::SUCCESS && status_ != Status::FAILURE;
    }

    void HttpRequestParser::parse(const char *p) {
        for( ;*p != '\0'; p++) {
            if(!parseOne(*p)) {
                status_ = Status::FAILURE;
                return;
            }
        }
    }

    bool HttpRequestParser::parseOne(char ch) {
        switch (status_) {
            case Status::SUCCESS:
            case Status::FAILURE:
                return false;
            case Status::OPEN_PARSING_METHOD:
                return onParsingMethod(ch);
            case Status::OPEN_PARSED_METHOD:
                return onParsedMethod(ch);
            case Status::OPEN_PARSING_URI:
                return onParsingUri(ch);
            case Status::OPEN_PARSED_URI:
                return onParsedUri(ch);
            case Status::OPEN_PARSING_VERSION:
                return onParsingVersion(ch);
            case Status::OPEN_PARSED_VERSION:
                return onParsedVersion(ch);
            case Status::OPEN_PARSING_HEADER:
                return onParsingHeader(ch);
            case Status::OPEN_PARSING_HEADER_NAME:
                return onParsingHeaderName(ch);
            case Status::OPEN_PARSED_HEADER_NAME:
                return onParsedHeaderName(ch);
            case Status::OPEN_PARSING_HEADER_VALUE:
                return onParsingHeaderValue(ch);
            case Status::OPEN_PARSED_HEADER_VALUE:
                return onParsedHeaderValue(ch);
            case Status::OPEN_NEED_FINAL_LF:
                return onNeedFinalLf(ch);
        }
        return false;
    }

#define FROM_STRING(...) if(!FromString(__VA_ARGS__)) { return false; }

    bool HttpRequestParser::onParsingMethod(char ch) {
        if (isupper(ch)) {
            buffer_.push_back(ch);
        } else if (ch == ' ') {
            FROM_STRING(buffer_.c_str(), request_.method_);
            go(Status::OPEN_PARSED_METHOD);
        } else {
            return false;
        }
        return true;
    }

    bool HttpRequestParser::onParsingUri(char ch) {
        if (!isspace(ch)) {
            buffer_.push_back(ch);
        } else if (ch == ' ') {
            request_.uri_ = std::move(buffer_);
            go(Status::OPEN_PARSED_URI);
        } else if (ch == '\r' && request_.method_ == HttpMethod::GET) {
            request_.uri_ = std::move(buffer_);
            request_.version_ = HttpVersion::HTTP_0_9;
            go(Status::OPEN_PARSED_VERSION);
        } else {
            return false;
        }
        return true;
    }

    bool HttpRequestParser::onParsingVersion(char ch) {
        if (isalnum(ch) || ch == '/' || ch == '.') {
            buffer_.push_back(ch);
        } else if (ch == '\r') {
            FROM_STRING(buffer_.c_str(), request_.version_);
            go(Status::OPEN_PARSED_VERSION);
        } else {
            return false;
        }
        return true;
    }

    bool HttpRequestParser::onParsingHeader(char ch) {
        if (!isspace(ch)) {
            go(Status::OPEN_PARSING_HEADER_NAME);
            buffer_.push_back(ch);
        } else if (ch == '\r') {
            go(Status::OPEN_NEED_FINAL_LF);
        } else {
            return false;
        }
        return true;
    }

    bool HttpRequestParser::onParsingHeaderName(char ch) {
        if(ch == ':') {
            headerToParse = request_.headers_.insert({std::move(buffer_), ""}).first;
            go(Status::OPEN_PARSED_HEADER_NAME);
        } else if (!isspace(ch)) {
            buffer_.push_back(ch);
        } else {
            return false;
        }
        return true;
    }

    bool HttpRequestParser::onParsingHeaderValue(char ch) {
        if (ch != '\r' && ch != '\n') {
            buffer_.push_back(ch);
        } else if (ch == '\r') {
            headerToParse->second = std::move(buffer_);
            headerToParse = request_.headers_.end();
            go(Status::OPEN_PARSED_HEADER_VALUE);
        } else {
            return false;
        }
        return true;
    }

    bool HttpRequestParser::onParsedMethod(char ch) {
        if (ch == ' ') {
            return true;
        } else if (!isspace(ch)) {
            go(Status::OPEN_PARSING_URI);
            buffer_.push_back(ch);
            return true;
        } else {
            return false;
        }
    }

    bool HttpRequestParser::onParsedUri(char ch) {
        if (ch == ' ') {
            return true;
        } else if (ch == 'H') {
            go(Status::OPEN_PARSING_VERSION);
            buffer_.push_back(ch);
            return true;
        } else {
            return false;
        }
    }

    bool HttpRequestParser::onParsedVersion(char ch) {
        if (ch == '\n') {
            go(Status::OPEN_PARSING_HEADER);
            return true;
        } else {
            return false;
        }
    }

    bool HttpRequestParser::onParsedHeaderName(char ch) {
        if (ch == ' '){
            return true;
        } else if (!isspace(ch)) {
            go(Status::OPEN_PARSING_HEADER_VALUE);
            buffer_.push_back(ch);
            return true;
        } else {
            return false;
        }
    }

    bool HttpRequestParser::onParsedHeaderValue(char ch) {
        if (ch == '\n') {
            go(Status::OPEN_PARSING_HEADER);
        } else {
            return false;
        }
        return true;
    }

    bool HttpRequestParser::onNeedFinalLf(char ch) {
        if (ch == '\n') {
            go(Status::SUCCESS);
            return true;
        } else {
            return false;
        }
    }

    void HttpRequestParser::go(Status status) {
        buffer_.clear();
        status_ = status;
    }

#undef FROM_STRING
}