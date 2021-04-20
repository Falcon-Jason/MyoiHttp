//
// Created by jason on 2021/4/21.
//

#ifndef NETWORK_HTTPREQUEST_H
#define NETWORK_HTTPREQUEST_H

#include <string>
#include <map>

enum class HttpRequestMethod {
    GET,
    POST
};

class HttpRequest {
private:
    HttpRequestMethod method;
    std::string path;
    std::string version;
    map<string, string> headers;
    string query;
};

#endif //NETWORK_HTTPREQUEST_H
