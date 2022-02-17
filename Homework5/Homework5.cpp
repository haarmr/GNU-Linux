#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <sys/types.h>
#include <cerrno>
#include <cstring>
#include <sys/wait.h>
#include "IPCService.h"

int main(int argc, char** argv) 
{
	// make sure all arguments passed
    if (argc < 3){
        std::cout<< "Insuficent arguments";
        exit(0);
    }   

	// get arguments and convert to int
    int arraySize = atoi(argv[1]);
    int workers = atoi(argv[2]);

	// create service instance
	IPCService *ipcService = new IPCService(arraySize, workers);

	// calculate sum with child proccesses
	int parallelSum = ipcService->calculate_sum();

	// calculate sum without threads or proccesses
	int sum = ipcService->sum_synchron();

	// output
	std::cout << "Synchron sum is: " << sum << std::endl;
	std::cout << "Parallel sum is: " << parallelSum << std::endl;
	
    return 0;
}
