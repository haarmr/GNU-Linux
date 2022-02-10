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
            this->matrix[i][j] = rand() % 100;
        }
    }
}


int ParallelMatrix::get_random_number()
{
    srand(time(0));  // Initialize random number generator.
 
  
    return (rand() % 10) + 1;  

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
    int size = this->height;
    int eachThreadStrength = ceil( (float)size/threadsCount);

    std::cout << "matrix size is :" << size << std::endl;
    std::cout << "thread count :" << threadsCount << std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;

    //std::cout << "eachThreadStrength :" << eachThreadStrength << std::endl;

    for(int i=0;i <threadsCount; i++) {

        //std::cout << "Thread " << i << " starting" <<std::endl;

        int startMatrixIndex = i*eachThreadStrength;      
        struct thread_args args;
        
        args.i = startMatrixIndex;
        args.strength = eachThreadStrength;
        args.arr = this->matrix;
            
        int result = pthread_create(&threads[i], NULL, thread_start, &args);

        if (result != 0) {
            exit(result);
        }
    }

    for(int i=0;i <threadsCount; i++) {

        void* retval;
        pthread_join(threads[i], &retval);
    }

    /*int sum=0;

    for (int i=0;i<10;i++) {
        for(int j=0;j<10;j++) {
            std::cout<< this->matrix[i][j] << " ";
            sum += this->matrix[i][j];
        }
        std::cout << std::endl;
    }*/

    return 0;
}

void* ParallelMatrix::thread_start(void* arg)
{
    //std::cout << "argpointer is " << *arg<<  std::endl;
    struct thread_args* args = (struct thread_args*) arg;

    std::cout << "startMatrixIndex: "<< &args->i << std::endl;
    std::cout << "eachThreadStrength: "<< &args->strength << std::endl;
    

    for (int startIndex=args->i; startIndex < args->strength; startIndex+=19) {
        
    }

    //std::cout << "startMatrixIndex: "<< args->i << std::endl;
    while (true) {
        
        //int size = sizeof(pThis->matrix)/sizeof(pThis->matrix[0]);


        
        

    }
    
}

/*void ParallelMatrix::increment_matrix_index()
{
    pthread_mutex_lock(&this->mutexIndexSt);

    this->subMatrixIndex++;

    pthread_mutex_unlock(&this->mutexIndexSt);

}

void ParallelMatrix::increment_matrix_index(int count)
{
    pthread_mutex_lock(&this->mutexSumSt);

    this->sum_parallel += count;

    pthread_mutex_unlock(&this->mutexSumSt);

}
*/