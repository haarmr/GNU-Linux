#include "IPCService.h"
#include <iostream>
#include <sys/types.h>
#include <unistd.h> 
#include <string.h>
#include <sys/wait.h> 

IPCService::IPCService(int arraySize, int workers)
{
    this->workers = workers;
    this->arraySize = arraySize;
    this->myArray = new int[this->arraySize];
    
    for (int i=0;i<this->arraySize;i++){
        myArray[i] = rand() % 100;
    }

    /*for (int i=0;i<this->arraySize;i++){
        std::cout<< myArray[i];
    }*/
}

void IPCService::calculate_sum()
{
    for (int i=0; i < this->workers; i++) {

        //std::cout<< "i: " << i << std::endl;
        // child only read from parent
        int parentToChild[2];

        // child only write from parent
        int childToParent[2];
    
        int result = pipe(parentToChild);
        int result2 = pipe(childToParent);

        int child = fork();

        // unable to create child
        if (child == -1) {
            exit(0);
        }

        // entered child
        if (child == 0) {

            // close unused pipes
            close(parentToChild[1]);
            close(childToParent[0]);
        
            char* buffer = new char[4];

            int readBytes = read(parentToChild[0], buffer, 4);

            std::cout << buffer << std::endl;

            exit;
        }
        else {

            // close unused pipes
            close(parentToChild[0]);
            close(childToParent[1]);

            //wait(NULL);

            const char* buffer = "asd";
            int size = strlen(buffer);


            std::cout << "size: is :::: " << size+1 << std::endl;
            int written = write(parentToChild[0], buffer, size+1);
                       
            wait(NULL);
        }

    }

    //while(wait(NULL) > 0);
}
