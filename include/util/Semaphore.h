/**
 * @file Semaphore.h
 * @author Jason Cheung
 * @date 2021.08.11
 */

#ifndef MYOI_SEMAPHORE_H
#define MYOI_SEMAPHORE_H

#include <semaphore.h>

namespace myoi {
    class Semaphore {
    private:
        sem_t sem_{};

    public:
        Semaphore() { sem_init(&sem_, 0, 0); }

        ~Semaphore() { sem_destroy(&sem_); }

        int wait() { return ::sem_wait(&sem_); }

        int post() { return ::sem_post(&sem_); }

        int tryWait() { return ::sem_trywait(&sem_); }
    };
}

#endif //MYOI_SEMAPHORE_H
