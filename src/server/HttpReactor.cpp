//
// Created by jason on 2021/8/14.
//

#include "server/HttpReactor.h"

namespace myoi {
    int HttpReactor::exec()  {
        bool success = this->open(64);
        if (!success) { return EXIT_FAILURE; }

        success = handler_->init(
                myoi::InetAddress{"127.0.0.1", 8080}, this);
        if (!success) { return EXIT_FAILURE; }

        return EventReactor::exec();
    }
}