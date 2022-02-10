#include <iostream>
#include <pthread.h>
#include "ParallelMatrix.h"
#include <unistd.h>
#include <cstdlib>



ParallelMatrix::ParallelMatrix()
{
    for (int i=0;i<10;i++) {
        for(int j=0;j<10;j++) {
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
    for (int i=0;i<10;i++) {
        for(int j=0;j<10;j++) {
            std::cout<< this->matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 1;
}