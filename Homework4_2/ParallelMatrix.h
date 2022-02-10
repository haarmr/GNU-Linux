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
            int **arr;
        };
    public:
        ParallelMatrix(int height, int weight);
        int sum();
        int sum_parallel(int threadCount);
        int get_random_number();
        static void* thread_start(void* arg);
        //void increment_matrix_index();
        //void increment_parallel_sum(int count);
};

#endif