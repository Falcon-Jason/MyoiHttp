//
// Created by jason on 25/4/21.
//

#ifndef NETWORK_HTTP_H
#define NETWORK_HTTP_H

#include "http/HttpResponse.h"
#include "http/HttpRequest.h"

namespace network {
    void ParseRequest(BufferedIo &in, HttpRequest &request);
    void ParseResponse(BufferedIo &in, HttpResponse &response);
    std::string GenerateRequest(const HttpRequest& request);
    std::string GenerateResponse(const HttpResponse &response);
}



#endif //NETWORK_HTTP_H
