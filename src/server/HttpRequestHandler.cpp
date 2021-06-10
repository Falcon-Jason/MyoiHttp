//
// Created by jason on 8/6/21.
//

#include "server/HttpRequestHandler.h"

#include <fmt/format.h>

#include <fcntl.h>
#include <sys/sendfile.h>

namespace myoi {
    using std::string, std::map;

    const map<int, string> HttpRequestHandler::StatusInfo_{
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

    void HttpRequestHandler::init(const HttpRequest &request, const string &baseDir) {
        if (request.method() == HttpMethod::POST) {
            initError(501);
        }

        string path = baseDir + request.uri();
        if (path.back() == '/') { path.append("index.html"); }
        file_.setFile(path.c_str());
        if (!file_.exists()) { return initError(404); }
        if (!file_.readable()) { return initError(403); }

        response_.status_ = 200;
        response_.version_ = request.version();
        response_.headers_["Close"] = "true";
        response_.headers_["Content-length"] = fmt::format("{}", file_.size());
        hasDataToSend_ = (request.method() != HttpMethod::HEAD);
    }

    void HttpRequestHandler::initError(int errCode) {
        response_.status_ = errCode;
        response_.version_ = HttpVersion::HTTP_1_0;
        response_.headers_["Close"] = "true";
        hasDataToSend_ = false;
    }

    bool HttpRequestHandler::writeTo(const TcpSocket &connection) {
        using std::string;
        using fmt::format;
        string header;
        header.append(format("{} {} {}\r\n",
                             ToString(response_.version_),
                             response_.status_,
                             StatusInfo(response_.status_)));
        for(auto &i : response_.headers_) {
            header.append(format("{}: {}\r\n", i.first, i.second));
        }
        header.append("\r\n");

        auto ret = connection.tryWrite(header.data(), header.size());
        return (ret > 0);
    }

    bool HttpRequestHandler::sendDataTo(const TcpSocket &connection) {
        int fildes = ::open(file_.filename(), O_RDONLY);
        if (fildes < 0) { return false; }
        ssize_t ret = ::sendfile(connection.index(), fildes, nullptr, file_.size());
        return (ret >= 0);
    }
}