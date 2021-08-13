//
// Created by jason on 2021/8/14.
//

#ifndef MYOI_HTTPREACTOR_H
#define MYOI_HTTPREACTOR_H

#include "server/HttpHandler.h"
#include "event/EventReactor.h"

#include <memory>
#include <csignal>

namespace myoi {
    class HttpReactor : public EventReactor {
    private:
        std::unique_ptr<HttpHandler> handler_{nullptr};

    public:
        HttpReactor(const char *baseDir, int nThread)
        : handler_{new HttpHandler{baseDir, nThread}}, EventReactor{} {}

        int exec() override;
    };
}

#endif //MYOI_HTTPREACTOR_H
