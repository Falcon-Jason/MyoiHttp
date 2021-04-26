//
// Created by jason on 24/4/21.
//
/**
 * To parse HttpRequest:
 * HttpRequest := RequestLine CRLF (Header CRLF)* CRLF Body
 * RequestLine := Method SP RequestUri SP HttpVersion
 * Header := FieldName ':' LWS FieldValue LWS
 * FieldName := (<any char except CTLs and tspecials>)+
 * Body := TEXT EOF
 */

#include "Http.h"

#include <boost/algorithm/string.hpp>
#include <vector>
#include <map>
#include <string>

using boost::trim_copy;
using boost::split;
using std::vector;
using std::map;
using std::string;

namespace network {

    constexpr int BUFFER_SIZE = 4096;
    static void ParseRequestLine(const string &line, HttpRequest &request);
    static void ParseHeader(const string &line, HttpRequest &request);
    static bool GetLine(BufferedIo &in, string &line);
    static void GetAllRest(BufferedIo &in, string &text);

    // HttpRequest := RequestLine CRLF (Header CRLF)* CRLF Body
    void ParseRequest(BufferedIo &in, HttpRequest &request) {
        string buffer;
        GetLine(in, buffer);
        ParseRequestLine(buffer, request);
        while (GetLine(in, buffer) && buffer != "\r\n") {
            ParseHeader(buffer, request);
        }

        if (request.method == HttpRequest::Method::INVALID) {
            request.error();
        }
    }


    void ParseResponse(BufferedIo &in, HttpResponse &response) {

    }

    // RequestLine := Method SP RequestUri SP HttpVersion
    static void ParseRequestLine(const string &line, HttpRequest &request) {
        vector<string> result;
        split(result, line, boost::is_space(), boost::token_compress_on);
        if (result.size() < 2) {
            request.error();
            return;
        }
        request.method = HttpRequest::StringToMethod(result[0].c_str());
        request.path = result[1];
        if (result.size() >= 3) {
            request.version = result[2];
        } else {
            request.version = "HTTP/0.9";
        }
    }

    // Header := FieldName ':' LWS FieldValue LWS
    // FieldName := (<any char except CTLs and tspecials>)+
    static void ParseHeader(const string &line, HttpRequest &request) {
        ssize_t index;
        bool isBroken = false;
        for( index = 0; index != line.size() && !isBroken; index++) {
            // in name
            switch (line[index]) {
                case 'a' ... 'z':
                case 'A' ... 'Z':
                case '0' ... '9':
                case '-':
                case '_':
                case '~':
                case '.':
                    break;
                case ':':
                    isBroken = true;
                    break;
                default:
                    request.error();
                    return;
            }
        }

        auto name = line.substr(0, index - 1);
        auto value = trim_copy(line.substr(index));
        request.headers[name] = value;
    }

    static bool GetLine(BufferedIo &in, string &line) {
        char buffer[BUFFER_SIZE];
        ssize_t length;
        if ((length = in.readline(buffer, BUFFER_SIZE)) <= 0) {
            return false; // EOF OR ERROR
        }

        line.clear();
        line.append(buffer);
        while (buffer[length - 1] != '\n') {
            length = in.readline(buffer, BUFFER_SIZE);
            line.append(buffer);
        }
        return true;
    }

    static void GetAllRest(BufferedIo &in, string &text) {
        char ch;
        text.clear();
        while(in.nread(&ch, 1) > 0) {
            text.push_back(ch);
        }
    }
}
