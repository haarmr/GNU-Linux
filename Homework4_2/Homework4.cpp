#include <iostream>
#include "ParallelMatrix.h"

int main() 
{
    ParallelMatrix *x = new ParallelMatrix();

    x->sum();
    return 0;
}