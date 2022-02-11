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
    if (argc < 3){
        std::cout<< "Insuficent arguments";
        exit(0);
    }   

    int arraySize = atoi(argv[1]);
    int workers = atoi(argv[2]);

	IPCService *ipcService = new IPCService(arraySize, workers);
	ipcService->calculate_sum();

	return 1;
    int pipefd[2];

    int result = pipe(pipefd);

    if (result != 0)
        exit(0);

    // the string to send
	const char* str = "Hello World";

	// size of string to write
	int size = strlen(str);

	// create a tez
	int child = fork();

	// exit on failure
	if(child == -1){
		exit(errno);
	}

	if(child == 0){

		char* buffer = new char[size + 1];
		std::cout << "Entered child process ..." << std::endl;	
	
		close(pipefd[1]);
		int readBytes = read(pipefd[0], buffer, size + 1); 

		std::cout << "Got text from parent: " << buffer << std::endl;
		
		delete [] buffer;
	}
	else {
		sleep(5);
		close(pipefd[0]);
		int written = write(pipefd[1], str, size + 1);		
		wait(NULL);
	}

    return 0;

}
