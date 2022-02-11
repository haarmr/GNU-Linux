#include <iostream>
#include <pthread.h>
#include "ParallelMatrix.h"
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>


ParallelMatrix::ParallelMatrix(int height, int weight)
{
    this->height = height;
    this->weight = weight;
    int mutex = pthread_mutex_init(&this->mutex, NULL);

    if (mutex != 0) {
        std::cout << "Error initalizin mutex" << std::endl;
        exit(0);
    }

    this->matrix = new int*[this->height];

    for (int i=0;i<this->height;i++) {
        this->matrix[i] =  new int[this->weight];

        for(int j=0;j<this->weight;j++) {
            this->matrix[i][j] = rand() % 1000;
        }
    }
}

int ParallelMatrix::sum()
{
    int sum=0;
    for (int i=0;i<this->height;i++) {
        for(int j=0;j<weight;j++) {
            //std::cout<< this->matrix[i][j] << " ";
            sum += this->matrix[i][j];
        }
        std::cout << std::endl;
    }

    return sum;
}

int ParallelMatrix::sum_parallel(int threadsCount)
{
    //this->sum_parallel = 0;
    pthread_t* threads = new pthread_t[threadsCount];
    this->paralleCounterSum = 0;
    int size = this->height;
    int eachThreadStrength = ceil( (float)size/threadsCount);

    /*std::cout << "matrix size is :" << size << std::endl;
    std::cout << "thread count :" << threadsCount << std::endl;
    

    std::cout << "eachThreadStrength :" << eachThreadStrength << std::endl;

    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;*/

    bool theEnd = false;

    for(int i=0;i <threadsCount; i++) {

        //std::cout << "Thread " << i << " starting" <<std::endl;

        int startMatrixIndex = i*eachThreadStrength;   

        //std::cout << "startMatrixIndex " << startMatrixIndex <<std::endl;
        //std::cout << "startMatrixIndex+eachThreadStrength " << startMatrixIndex+eachThreadStrength <<std::endl;

        // means reached the end
        if ((startMatrixIndex+eachThreadStrength) > size) {
            
            eachThreadStrength = size - startMatrixIndex;
            theEnd = true;
        }

        if (eachThreadStrength <= 0) {
            break;
        }

        thread_args* args = new (thread_args);
        
        //std::cout << "start from " << startMatrixIndex << " and iterate till this index of array " << startMatrixIndex+eachThreadStrength <<std::endl;


        args->i = startMatrixIndex;
        args->strength = eachThreadStrength;
        //args->weight = this->weight;
        //args->arr = this->matrix;
        args->myClass = this;
            
        int result = pthread_create(&threads[i], NULL, thread_start, args);

        if (result != 0) {
            exit(result);
        }

        if (theEnd)
            break;
    }

    for(int i=0;i <threadsCount; i++) {

        void* retval;
        //pthread_join(threads[i], &retval);
    }

    return this->paralleCounterSum;
}

void* ParallelMatrix::thread_start(void* arg)
{
    //std::cout << "argpointer is " << *arg<<  std::endl;
    struct thread_args* args = (struct thread_args*) arg;
    ParallelMatrix* pThis = (ParallelMatrix*) args->myClass;

    //std::cout << "startMatrixIndex: "<< args->i << std::endl;
    //std::cout << "eachThreadStrength: "<< args->strength << std::endl;
    

    for (int startIndex=args->i; startIndex < (args->strength+args->i); startIndex++) {
        for(int j=0;j<pThis->weight;j++) {
            pThis->increment_parallel_sum(pThis->matrix[startIndex][j]);
        }
    }

    return NULL;
}

void ParallelMatrix::increment_parallel_sum(int count)
{
    pthread_mutex_lock(&this->mutex);

    this->paralleCounterSum = this->paralleCounterSum + count;

    pthread_mutex_unlock(&this->mutex);

}
