#ifndef HEADFILE_H
#define HEADFILE_H

#include <pthread.h>

class ParallelMatrix 
{
    private:
        int matrix[1000][1000];
        //int subMatrixIndex;
        int paralleCounterSum;
        pthread_mutex_t mutex;
        //pthread_mutex_t mutexForSum;
    public:
        ParallelMatrix();
        int sum();
        int sum_parallel(int threadCount);
        int get_random_number();
        static void* thread_start(void* arg);
        //void increment_matrix_index();
        //void increment_parallel_sum(int count);
};

#endif
