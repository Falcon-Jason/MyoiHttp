/**
 * @file HttpHandler.h
 * @author Jason Cheung
 * @date 2021.06.25
 */

#ifndef MYOI_HTTPHANDLER_H
#define MYOI_HTTPHANDLER_H

#include "util/FixedThreadPool.h"
#include "event/EventHandler.h"
#include "event/EventReactor.h"
#include "HttpEvent.h"
#include "HttpProcessor.h"

#include <list>
#include <memory>
#include <string>
#include <mutex>
#include <thread>

namespace myoi {
    class HttpHandler : public EventHandler {
    public:
        constexpr static int BUFFER_SIZE = 1024;
        using EventSet = std::unordered_map<NativeHandle, std::unique_ptr<HttpEvent>>;

        struct Task {
            Event *event;
            EventReactor *reactor;
        };

        using TaskQueue = std::list<Task>;
        using ThreadPtr = std::unique_ptr<std::thread>;

    private:
        EventSet events_;
        std::string baseDir_;
        std::mutex mutex_;
        FixedThreadPool pool_;


    public:
        explicit HttpHandler(const char *baseDir, int nThread) noexcept
            : events_{}, mutex_{}, baseDir_{baseDir}, pool_{nThread} {}

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
