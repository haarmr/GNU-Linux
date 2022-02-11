#include <iostream>
#include "ParallelMatrix.h"
#include <cstdlib>
#include <chrono>

int main(int argc, char** argv) 
{
    if (argc < 3){
        std::cout<< "Insuficent arguments";
        exit(0);
    }   

    int matrixHeight = atoi(argv[1]);
    int matrixWeight = atoi(argv[2]);

    ParallelMatrix *x = new ParallelMatrix(matrixHeight, matrixWeight);

    auto startedSumSychron = std::chrono::high_resolution_clock::now();
    int sum = x->sum();
    auto doneSumSychron = std::chrono::high_resolution_clock::now();


    auto startedSumAsSychron = std::chrono::high_resolution_clock::now();
    int sumx = x->sum_parallel(atoi(argv[3]));
    auto doneSumASychron = std::chrono::high_resolution_clock::now();
    
    std::cout << "Sum is: " << sum << ", Time spent: ";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(doneSumSychron-startedSumSychron).count() << std::endl;

    std::cout<< "SumParallel is: " << sumx << ", Time spent: ";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(doneSumASychron-startedSumAsSychron).count() << std::endl;

    return 0;
}
