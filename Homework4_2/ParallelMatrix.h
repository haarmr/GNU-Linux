#ifndef HEADFILE_H
#define HEADFILE_H

class ParallelMatrix 
{
    private:
        int matrix[10][10];
    public:
        ParallelMatrix();
        int sum();
        int sum_parallel(int threadCount);
        int get_random_number();

};

#endif
