/**
 * @file HttpHandler.h
 * @author Jason Cheung
 * @date 2021.06.25
 */

#ifndef MYOI_HTTPHANDLER_H
#define MYOI_HTTPHANDLER_H

#include "util/Semaphore.h"
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
        std::mutex eventsMutex_;

        TaskQueue queue_;
        Semaphore queueSem_;
        std::mutex queueMutex_;

        HttpProcessor processor_;
        std::unique_ptr<ThreadPtr[]> threadPool_;

    public:
        explicit HttpHandler(const char *baseDir, unsigned int nThread) noexcept
            : events_{}, eventsMutex_{}, baseDir_{baseDir}, processor_{this},
              queue_{}, queueSem_{}, queueMutex_{}, threadPool_{} {
            threadPool_ = std::make_unique<ThreadPtr[]>(nThread);
            for (int i = 0; i < nThread; i++) {
                threadPool_[i] = std::make_unique<std::thread>(&HttpProcessor::start, &processor_);
                threadPool_[i]->detach();
            }
        }

        void handle(Event *e, EventReactor *reactor) override;

        bool init(const InetAddress &address, EventReactor *reactor);

        const std::string &baseDir() const { return baseDir_; }

        void terminate() { processor_.terminate(); }


    private:
        void listen(HttpEvent *event, EventReactor *reactor);

        void process(HttpEvent *event, EventReactor *reactor);

        void registerEvent(TcpSocket socket, EventReactor *reactor);

        void removeEvent(HttpEvent *event, EventReactor *reactor);

        friend class HttpProcessor;
    };
}



#endif //MYOI_HTTPHANDLER_H
