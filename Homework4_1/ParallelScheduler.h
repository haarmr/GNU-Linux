#ifndef HEADFILE_H
#define HEADFILE_H

#include <pthread.h>
#include <queue>
#include <functional>

class ParallelScheduler
{
    private:
        int count;
        struct Task {
            void* arg;
            void (*func)(void*);
        };
        pthread_t* threads;
        pthread_mutex_t mutex;
        pthread_cond_t cond;
        std::queue<Task> myFunctions;

    public:
        ParallelScheduler(int threadsCount);
        static void* thread_start(void* args);
        pthread_mutex_t* get_mutex();
        pthread_cond_t* get_cond();
        void run(void (*start_routine) (void*) , void* arg);
        void wait_for_threads();
};

#endif
