#include <iostream>
#include "ParallelMatrix.h"
#include <cstdlib>

int main(int argc, char** argv) 
{
    if (argc < 3){
        std::cout<< "Insuficent arguments";
        exit(0);
    }   

    int matrixHeight = atoi(argv[1]);
    int matrixWeight = atoi(argv[2]);

    ParallelMatrix *x = new ParallelMatrix(matrixHeight, matrixWeight);

    int sum = x->sum();
    

    int sumx = x->sum_parallel(atoi(argv[3]));
    
    std::cout << "Sum is: " << sum << std::endl;
    std::cout<< "SumParallel is: " << sumx << std::endl;

    return 0;
}