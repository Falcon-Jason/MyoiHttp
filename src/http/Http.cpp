//
// Created by jason on 28/5/21.
//
#include "http/HttpRequest.h"
#include <cstring>

namespace myoi {
    const char *ToString(HttpVersion version) {
        switch (version) {
            case HttpVersion::HTTP_0_9:
                return "HTTP/0.9";
            case HttpVersion::HTTP_1_0:
                return "HTTP/1.0";
            case HttpVersion::HTTP_1_1:
                return "HTTP/1.1";
        }
        return "";
    }

    bool FromString(const char *string, HttpVersion &version) {
        if (strcmp(string, "HTTP/0.9") == 0) {
            version = HttpVersion::HTTP_0_9;
        } else if (strcmp(string, "HTTP/1.0") == 0) {
            version = HttpVersion::HTTP_1_0;
        } else if (strcmp(string, "HTTP/1.1") == 0) {
            version = HttpVersion::HTTP_1_1;
        } else {
            return false;
        }

        return true;
    }

    const char *ToString(HttpMethod method) {
        using Method = HttpMethod;

        switch (method) {
            case Method::GET:
                return "GET";
            case Method::POST:
                return "POST";
            case Method::HEAD:
                return "HEAD";
        }
        return "";
    }

    bool FromString(const char *string, HttpMethod &method) {
        using Method = HttpMethod;

        if (strcmp(string, "GET") == 0) {
            method = Method::GET;
        } else if (strcmp(string, "POST") == 0) {
            method = Method::POST;
        } else if (strcmp(string, "HEAD") == 0) {
            method = Method::HEAD;
        } else {
            return false;
        }
        return true;
    }
}