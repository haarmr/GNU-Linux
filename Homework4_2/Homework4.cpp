#include <iostream>
#include "ParallelMatrix.h"

int main(int argc, char** argv) 
{
    if (argc < 3){
        std::cout<< "Insuficent arguments";
        exit(0);
    }   

    int matrixHeight = 500;
    int matrixWeight = 500;

    ParallelMatrix *x = new ParallelMatrix(matrixHeight, matrixWeight);

    //int sum = x->sum();
    
    //std::cout << "Sum is: " << sum << std::endl;

    int sumx = x->sum_parallel(2);

    return 0;
}