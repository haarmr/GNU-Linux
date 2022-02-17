#include <iostream>
#include <pthread.h>
#include "ParallelMatrix.h"
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>

/*
 * Create matrix with given size and fill random data
 */
ParallelMatrix::ParallelMatrix(int height, int weight)
{
    // get args
    this->height = height;
    this->weight = weight;

    // create mutex
    int mutex = pthread_mutex_init(&this->mutex, NULL);

    // make sure mutex created
    if (mutex != 0) {
        std::cout << "Error initalizin mutex" << std::endl;
        exit(0);
    }

    // for first create array of size
    this->matrix = new int*[this->height];

    // then for each value of array create new array and thus get the matrix
    for (int i=0;i<this->height;i++) {

        // create new array in array at position
        this->matrix[i] =  new int[this->weight];

        // fill random data
        for(int j=0;j<this->weight;j++) {
            this->matrix[i][j] = rand() % 1000;
        }
    }
}

/*
 * Calculate sum of matrix synchron
 */
int ParallelMatrix::sum()
{
    int sum=0;
    for (int i=0;i<this->height;i++) {
        for(int j=0;j<weight;j++) {
            //std::cout<< this->matrix[i][j] << " ";
            sum += this->matrix[i][j];
        }
        //std::cout << std::endl;
    }

    return sum;
}

/*
 * Calculate sum of matrix with threads
 */
int ParallelMatrix::sum_parallel(int threadsCount)
{
    // create threads store
    pthread_t* threads = new pthread_t[threadsCount];

    // set initial data
    this->paralleCounterSum = 0;
    int size = this->height;

    // get how many indexes each thread should carry
    int eachThreadStrength = ceil( (float)size/threadsCount);

    // make sure we didn`t reached end of the array
    bool theEnd = false;

    // create threads
    for(int i=0;i <threadsCount; i++) {

        // get starting index for calculation to pass to thread
        int startMatrixIndex = i*eachThreadStrength;   

        // make sure end not reached
        if ((startMatrixIndex+eachThreadStrength) > size) {
            
            // if ending index gets out of array size then set the last index
            eachThreadStrength = size - startMatrixIndex;

            // set the end reached
            theEnd = true;
        }

        // make sure our strength for threads is positive
        if (eachThreadStrength <= 0) {
            break;
        }

        // create args for thread
        thread_args* args = new (thread_args);
        
        // set data
        args->i = startMatrixIndex;
        args->strength = eachThreadStrength;
        args->myClass = this;
            
        // create thread and pass data
        int result = pthread_create(&threads[i], NULL, thread_start, args);

        // make sure thread created
        if (result != 0) {
            exit(result);
        }

        // after all break when array size reached end
        if (theEnd)
            break;
    }

    // wait for all threads to finish
    for(int i=0;i <threadsCount; i++) {

        void* retval;
        pthread_join(threads[i], &retval);
    }

    // return total sum
    return this->paralleCounterSum;
}

/*
 * Main thread execution body
 */
void* ParallelMatrix::thread_start(void* arg)
{
    // get argument
    struct thread_args* args = (struct thread_args*) arg;

    // get our instance from arguments
    ParallelMatrix* pThis = (ParallelMatrix*) args->myClass;

    // iterate through array and count sum
    int sum = 0;
    for (int startIndex=args->i; startIndex < (args->strength+args->i); startIndex++) {
        for(int j=0;j<pThis->weight;j++) {
            
            // add to sum
            sum += pThis->matrix[startIndex][j];
            
        }
    }

    pThis->increment_parallel_sum(sum);
    
    return NULL;
}

/*
 * Method increments total parallel counted sum and carries synchronization 
 */
void ParallelMatrix::increment_parallel_sum(int count)
{
    // lock the mutex
    pthread_mutex_lock(&this->mutex);

    // add value to sub total
    this->paralleCounterSum = this->paralleCounterSum + count;

    // unlock mutex
    pthread_mutex_unlock(&this->mutex);

}
