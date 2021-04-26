//
// Created by jason on 25/4/21.
//

#include "http/HttpResponse.h"
#include "Http.h"

#include <sys/stat.h>
#include <fcntl.h>

namespace network{
    std::string HttpResponse::toString() const {
        return GenerateResponse(*this);
    }

    void HttpResponse::parse(BufferedIo &in) {
        return ParseResponse(in, *this);
    }

    void HttpResponse::clear() {
        status.clear();
        version.clear();
        headers.clear();
        content.clear();
    }

    void HttpResponse::error(const char *stat) {
        clear();
        status = stat;
    }

    void HttpResponse::setContentFile(const char *filename) {
        struct ::stat fStat{};
        if(::stat(filename, &fStat) < 0) {
            this->status = "404";
        } else {
            if (!S_ISREG(fStat.st_mode) || !(S_IRUSR & fStat.st_mode)) {
                this->status = "403";
                this->content = HttpStatusInfo.at(status);
            } else {
                this->status = "200";
                constexpr int BUFFER_SIZE = 1024;
                char buffer[BUFFER_SIZE];
                BufferedIo in{open(filename, O_RDONLY, 0)};
                this->content.clear();
                while (in.readline(buffer, BUFFER_SIZE)) {
                    this->content.append(buffer);
                }
            }
            const char *suffix = strrchr(filename, '.');
            if (suffix != nullptr && ContentTypes.count(suffix)) {
                this->headers["Content-type"] = ContentTypes.at(suffix);
            } else {
                this->headers["Content-type"] = DEFAULT_CONTENT_TYPE;
            }
        }

        refreshContentLength();
    }

    void HttpResponse::refreshContentLength() {
        this->headers["Content-length"] = fmt::format("{}", this->content.length());
    }

    const std::map<std::string, std::string> HttpStatusInfo {
            { "200", "OK" },
            { "201", "Created" },
            { "202", "Accepted" },
            { "204", "No Content" },
            { "301", "Moved Permanently" },
            { "302", "Moved Temporarily" },
            { "304", "Not Modified" },
            { "400", "Bad Request" },
            { "401", "Unauthorized" },
            { "403", "Forbidden" },
            { "404", "Not Found" },
            { "500", "Internal Server Error" },
            { "501", "Not Implemented" },
            { "502", "Bad Gateway" },
            { "503", "Service Unavailable" },
    };

    const std::map<std::string, std::string> ContentTypes {
            {".htm", "text/html"},
            {".html", "text/html"},
            {".txt", "text/plain"},
            {".gif", "text/gif"},
            {".jpg", "text/jpg"},
            {".jpeg", "text/jpg"},
            {".png", "text/png"}
    };
};
