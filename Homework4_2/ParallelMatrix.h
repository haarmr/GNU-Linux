#ifndef HEADFILE_H
#define HEADFILE_H

#include <pthread.h>

class ParallelMatrix 
{
    private:
        int height;
        int weight;
        int **matrix;
        int paralleCounterSum;
        pthread_mutex_t mutex;
        struct thread_args{
            int i;
            int strength;
            void* myClass;
        };
    public:
        ParallelMatrix(int height, int weight);
        int sum();
        int sum_parallel(int threadCount);
        static void* thread_start(void* arg);
        void increment_parallel_sum(int count);
};

#endif
