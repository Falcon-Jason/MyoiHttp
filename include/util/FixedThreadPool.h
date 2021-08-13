//
// Created by jason on 2021/8/14.
//

#include <thread>
#include <vector>
#include <list>
#include <mutex>
#include <condition_variable>
#ifndef MYOI_FIXEDTHREADPOOL_H
#define MYOI_FIXEDTHREADPOOL_H


namespace myoi {
    class Task {
    public:
        virtual void run() = 0;
        virtual ~Task() = default;
    };

    class FixedThreadPool {
    private:
        std::vector<std::thread> threads_;
        std::list<std::shared_ptr<Task>> tasks_;
        std::mutex mutex_;
        std::condition_variable notifier_;
        bool terminate_;

        void threadRun(int id);

    public:
        explicit FixedThreadPool(int threadsCount);

        ~FixedThreadPool();

        void submit(const std::shared_ptr<Task>& task);
    };

}




#endif //MYOI_FIXEDTHREADPOOL_H
