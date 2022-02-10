#include <iostream>
#include "ParallelScheduler.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>

void myfunction(void* arg) 
{    

    int* number = (int*) arg;
    std::cout << "MYFUNTION EXECUTED " <<  *number << std::endl;

}

int main() 
{
    // number of threads
	int threadsCount = 32;

    ParallelScheduler* scheduler = new ParallelScheduler(threadsCount);
    
    int simpleArg = 1;
    
    for (int i =0;i< 1111; i++) {
        scheduler->run(myfunction, new int(i));
    }
    
    scheduler->wait_for_threads();
    
    return 0;
}