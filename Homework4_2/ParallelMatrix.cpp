#include <iostream>
#include <pthread.h>
#include "ParallelMatrix.h"
#include <unistd.h>
#include <cstdlib>
#include <cmath>


ParallelMatrix::ParallelMatrix()
{
    int mutex = pthread_mutex_init(&this->mutex, NULL);

    if (mutex != 0) {
        std::cout << "Error initalizin mutex" << std::endl;
        exit(0);
    }

    for (int i=0;i<1000;i++) {
        for(int j=0;j<1000;j++) {
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
    for (int i=0;i<1000;i++) {
        for(int j=0;j<1000;j++) {
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
    int size = sizeof(this->matrix)/sizeof(this->matrix[0]);
    int eachThreadStrength = ceil( (float)size/threadsCount);


    std::cout << "matrix size is :" << size << std::endl;
    std::cout << "thread count :" << threadsCount << std::endl;

    std::cout << "eachThreadStrength :" << eachThreadStrength << std::endl;

    return 1;
    for(int i=0;i <=threadsCount; i++) {

        int startMatrixIndex = i*eachThreadStrength;
        int submatrix[eachThreadStrength][1000];

        
        for(int j=0;j<eachThreadStrength;j++) {

            submatrix[j] = this->matrix[startMatrixIndex];
            startMatrixIndex++;
            
            if (startMatrixIndex > size){
                break;
            }
        }
        
        

        int result = pthread_create(&threads[i], NULL, thread_start, this);

        if (result != 0) {
            exit(result);
        }
    }

    for(int i=0;i <=threadsCount; i++) {

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
    ParallelMatrix *pThis = (ParallelMatrix*) arg;

    while (true) {
        
        int size = sizeof(pThis->matrix)/sizeof(pThis->matrix[0]);


        
        

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