#include <iostream>
#include "ParallelScheduler.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>

/*
 * Method to run in scheduler
 */
void myfunction(void* arg) 
{    
    int* number = (int*) arg;
    std::cout << "MYFUNTION EXECUTED " <<  *number << std::endl;

    delete number;
}

int main() 
{
    // number of threads
	int threadsCount = 88;

    // create our schedulre with requred threads
    ParallelScheduler* scheduler = new ParallelScheduler(threadsCount);
    
    // run out functions to scheduler
    for (int i=0;i < 100000; i++) {
        scheduler->run(myfunction, new int(i));
    }
    
    // wait for all threads to exit and quit
    scheduler->wait_for_threads();
    
    return 0;
}