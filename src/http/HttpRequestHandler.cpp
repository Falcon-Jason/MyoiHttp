//
// Created by jason on 8/6/21.
//

#include "core/FileInfo.h"
#include "http/HttpRequestHandler.h"
#include <fmt/format.h>

namespace myoi {
    const std::map<int, std::string> HttpRequestHandler::StatusInfo_{
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

    void HttpRequestHandler::init(const HttpRequest &request) {
        initError(200);
    }

    void HttpRequestHandler::initError(int errCode) {
        response.status_ = errCode;
        response.version_ = HttpVersion::HTTP_1_0;
        response.headers_["Close"] = "true";
        const char *errInfo = StatusInfo(errCode);

        data = fmt::format("<h1>{} {}</h1> <p>{}</p>",
                           errCode, errInfo, errInfo);
    }

    bool HttpRequestHandler::writeTo(TcpSocket &connection) {
        using std::string;
        using fmt::format;
        string header;
        header.append(format("{} {} {}\r\n",
                             ToString(response.version_),
                             response.status_,
                             StatusInfo(response.status_)));
        for(auto &i : response.headers_) {
            header.append(format("{}: {}\r\n", i.first, i.second));
        }
        header.append("\r\n");

        auto ret = connection.tryWrite(header.data(), header.size());
        if (ret <= 0) { return false; }
        ret = connection.tryWrite(data.data(), data.size());
        return (ret >= 0);
    }
}