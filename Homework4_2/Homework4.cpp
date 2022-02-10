#include <iostream>
#include "ParallelMatrix.h"

int main() 
{
    ParallelMatrix *x = new ParallelMatrix();

    int sum = x->sum();
    
    std::cout << "Sum is: " << sum << std::endl;

    int sumx = x->sum_parallel(20);

    return 0;
}