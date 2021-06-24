/**
 * @file HttpHandler.h
 * @author Jason Cheung
 * @date 2021.06.25
 */

#ifndef MYOI_HTTPHANDLER_H
#define MYOI_HTTPHANDLER_H

#include "event/EventHandler.h"
#include "event/EventReactor.h"
#include "HttpEvent.h"
#include "HttpProcessor.h"

#include <memory>
#include <unordered_map>
#include <string>
#include <mutex>

namespace myoi {
    class HttpHandler : public EventHandler {
    public:
        constexpr static int BUFFER_SIZE = 1024;
        using EventSet = std::unordered_map<NativeHandle, std::unique_ptr<HttpEvent>>;

    private:
        EventSet events_;
        std::mutex eventsMutex;
        std::string baseDir_;

    public:
        explicit HttpHandler(const char *baseDir) noexcept
            : events_{}, eventsMutex{}, baseDir_{baseDir} {}

        void handle(Event *e, EventReactor *reactor) override;

        bool init(const InetAddress &address, EventReactor *reactor);

        const std::string &baseDir() const { return baseDir_; }

    private:
        void listen(HttpEvent *event, EventReactor *reactor);

        void process(HttpEvent *event, EventReactor *reactor);

        void registerEvent(TcpSocket socket, EventReactor *reactor);

        void removeEvent(HttpEvent *event, EventReactor *reactor);

        friend class HttpProcessor;
    };
}



#endif //MYOI_HTTPHANDLER_H
