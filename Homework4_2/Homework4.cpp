#include <iostream>
#include "ParallelMatrix.h"
#include <cstdlib>
#include <chrono>

int main(int argc, char** argv) 
{
    // make sure all arguments passed
    if (argc < 4){
        std::cout<< "Insuficent arguments";
        exit(0);
    }   

    // get arguments from input and convert to int
    int matrixHeight = atoi(argv[1]);
    int matrixWeight = atoi(argv[2]);

    // init parallel matrix with random data of given size
    ParallelMatrix *x = new ParallelMatrix(matrixHeight, matrixWeight);

    // start timer
    auto startedSumSychron = std::chrono::high_resolution_clock::now();

    // calculate sum of matrix without threads
    int sum = x->sum();

    // stop timer
    auto doneSumSychron = std::chrono::high_resolution_clock::now();

    // start timer
    auto startedSumAsSychron = std::chrono::high_resolution_clock::now();

    // calculate sum of matrix with threads of given number
    int sumx = x->sum_parallel(atoi(argv[3]));

    // stop timer
    auto doneSumASychron = std::chrono::high_resolution_clock::now();
    
    // print required data
    std::cout << "Sum is: " << sum << ", Time spent: ";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(doneSumSychron-startedSumSychron).count() << std::endl;

    std::cout<< "SumParallel is: " << sumx << ", Time spent: ";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(doneSumASychron-startedSumAsSychron).count() << std::endl;

    return 0;
}
