//
// Created by jason on 25/4/21.
//

#include "http/HttpRequest.h"
#include "http/HttpResponse.h"
#include "Http.h"
#include <fmt/format.h>

using std::string;
using std::map;
using fmt::format;

namespace network {
    template<class ...T>
    static void WriteLine(string &str, const char *format, T ...t) {
        str.append(::format(format, t...));
        str.append("\r\n");
    }

    static void WriteLine(string &str) {
        str.append("\r\n");
    }

    template<class ...T>
    static void WriteLine(BufferedIo &out, const char *format, T ...t) {
        auto line = format(format, t...);
        out.nwrite(line.c_str(), line.size());
        out.nwrite("\r\n", 2);
    }

    static void WriteLine(BufferedIo &out) {
        out.nwrite("\r\n", 2);
    }

    static void GenerateHeaders(string &str, const map<string, string> &headers) {
        for (auto &item : headers) {
            WriteLine(str, "{}:{}",
                      item.first, item.second);
        }
    }

    string GenerateRequest(const HttpRequest& request) {
        string result{};
        WriteLine(result, "{} {} {}",
                  HttpRequest::MethodToString(request.method),request.path,request.version);

        GenerateHeaders(result, request.headers);

        WriteLine(result);
        result.append(request.content);
        return result;
    }

    string GenerateResponse(const HttpResponse &response) {
        string result{};
        string statusInfo = HttpStatusInfo.count(response.status) ?
                                 HttpStatusInfo.at(response.status) : "No StatusInfo";

        WriteLine(result, "{} {} {}", response.version, response.status, statusInfo);

        if (!response.headers.count("Content-length")) {
            WriteLine(result, "Content-length:{}", response.content.size());
        }
        GenerateHeaders(result, response.headers);

        WriteLine(result);

        if (response.status[0] == '2') {
            result.append(response.content);
        } else {
            result.append(statusInfo);
        }

        return result;
    }
}