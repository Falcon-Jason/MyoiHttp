//
// Created by jason on 28/5/21.
//
#include "util/HttpUtil.h"
#include <cstring>
#include <fmt/format.h>
namespace myoi {

    HttpVersion
        HttpVersion::HTTP_0_9{"HTTP/0.9"},
        HttpVersion::HTTP_1_0{"HTTP/1.0"},
        HttpVersion::HTTP_1_1{"HTTP/1.1"};

    bool HttpVersion::parse(HttpVersion &version, const char *str) {
        if (strcmp(str, HTTP_0_9.toString()) == 0) {
            version = HttpVersion::HTTP_0_9;
        } else if (strcmp(str, HTTP_1_0.toString()) == 0) {
            version = HttpVersion::HTTP_1_0;
        } else if (strcmp(str, HTTP_1_1.toString()) == 0) {
            version = HttpVersion::HTTP_1_1;
        } else {
            return false;
        }

        return true;
    }

    HttpMethod
        HttpMethod::GET{"GET"},
        HttpMethod::POST{"POST"},
        HttpMethod::HEAD{"HEAD"};

    bool HttpMethod::parse(HttpMethod &method, const char *str) {
        using Method = HttpMethod;

        if (strcmp(str, "GET") == 0) {
            method = GET;
        } else if (strcmp(str, "POST") == 0) {
            method = POST;
        } else if (strcmp(str, "HEAD") == 0) {
            method = HEAD;
        } else {
            return false;
        }

        return true;
    }

    std::string HttpResponse::toString() const {
        using std::string;
        using fmt::format;
        string response;
        response.append(format("{} {} {}\r\n",
                               version_.toString(),
                               status_,
                               StatusInfo(status_)));
        for(auto &i : headers_) {
            response.append(format("{}: {}\r\n", i.first, i.second));
        }
        response.append("\r\n");

        return response;
    }

    const std::map<int, std::string> HttpResponse::StatusInfo_{
            {200, "OK"},
            {201, "Created"},
            {202, "Accepted"},
            {204, "No Content"},
            {301, "Moved Permanently"},
            {302, "Moved Temporarily"},
            {304, "Not Modified"},
            {400, "Bad Request"},
            {401, "Unauthorized"},
            {403, "Forbidden"},
            {404, "Not Found"},
            {500, "Internal Server Error"},
            {501, "Not Implemented"},
            {502, "Bad Gateway"},
            {503, "Service Unavailable"},
    };



}