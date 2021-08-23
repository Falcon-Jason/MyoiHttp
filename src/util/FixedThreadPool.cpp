//
// Created by jason on 2021/8/14.
//

#include <cassert>
#include <fmt/format.h>

#include "util/FixedThreadPool.h"

namespace myoi {
    FixedThreadPool::FixedThreadPool(int threadsCount)
            : threads_{}, tasks_{}, mutex_{}, notifier_{}, terminate_{false} {
        for (int i = 0; i < threadsCount; i++) {
            threads_.emplace_back(&FixedThreadPool::threadRun, this, i);
        }
        fmt::print(stderr, "[INFO] Initialized Fixed Thread Pool with {} threads\n", threadsCount);
    }

    void FixedThreadPool::threadRun(int id) {
        while (true) {
            std::shared_ptr<Task> task{nullptr};

            do {
                std::unique_lock<std::mutex> lock{mutex_};
                notifier_.wait(lock, [this]() { return terminate_ || !tasks_.empty(); });
                if (terminate_ || tasks_.empty()) {
//                    fmt::print(stderr, "[INFO] Thread {} stopped\n", id);
                    return;
                }
                task = tasks_.front();
                tasks_.pop_front();
            } while (false);

            task->operator()();
        }


    }

    FixedThreadPool::~FixedThreadPool() {
        mutex_.lock();
        terminate_ = true;
        mutex_.unlock();
        notifier_.notify_all();
        for (auto &th : threads_) {
            th.join();
        }

        fmt::print(stderr, "[INFO] Closed Thread Pool with {} threads\n", threads_.size());
    }

    void FixedThreadPool::submit(const std::shared_ptr<Task> &task) {
        mutex_.lock();
        assert(!terminate_);
        tasks_.emplace_back(task);
        mutex_.unlock();
        notifier_.notify_one();
    }
}