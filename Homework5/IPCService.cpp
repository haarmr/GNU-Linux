#include "IPCService.h"
#include <iostream>
#include <sys/types.h>
#include <unistd.h> 
#include <string.h>
#include <sys/wait.h> 
 #include <math.h> 

IPCService::IPCService(int arraySize, int workers)
{
    this->workers = workers;
    this->arraySize = arraySize;
    this->myArray = new int[this->arraySize];
    
    for (int i=0;i<this->arraySize;i++){
        myArray[i] = rand() % 1000;
    }
}

int IPCService::sum_synchron()
{
    int sum=0;
    for(int i=0;i<this->arraySize;i++) {
        sum += this->myArray[i];
    }

    return sum;
}

int IPCService::calculate_sum()
{
    int eachWorkerStrength = ceil((float) this->arraySize/this->workers);
    int *subTotalOfWorkes = new int[this->workers];
    bool isEnd = false;
    int calculatedTotal = 0;

    //std::cout<<eachWorkerStrength;
    //return;
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
        
            
            int *data = new int[2];
            //std::cout<<"reading bytes" << std::endl;
            int readBytes = read(parentToChild[0], data, sizeof(data));

            //std::cout << getpid() <<"- I will take from: " << data[0] << " to: " << data[1] << std::endl;

            int* childCountedSum = new int();
            for (int j=data[0]; j<data[1]; j++) {
                *childCountedSum += this->myArray[j];
                //std::cout << "J is: " << j << "  ";
                //std::cout << this->myArray[j] << std::endl;
            }

            //std::cout<< "One of workers calculated sum: " << *childCountedSum << std::endl;

            
            int written = write(childToParent[1], childCountedSum, sizeof(childCountedSum));

            if (written == -1) {
                std::cout<< strerror(errno);
                exit(0);
            }
            //sleep(2);

            // exit to prevent chil to enter out loop and start another childs
            exit(0);
        }
        else {

            // close unused pipes
            close(parentToChild[0]);
            close(childToParent[1]);

            int workerStartIndex = i*eachWorkerStrength;
            int workerEndIndex = workerStartIndex + eachWorkerStrength;

            if (workerEndIndex >= this->arraySize) {
                workerEndIndex = this->arraySize;
                isEnd = true;
            }

            int* data = new int[2];
            data[0] = workerStartIndex;
            data[1] = workerEndIndex;
            
            //std::cout <<"child will take: " << data[0] << " to: " << data[1] << std::endl;

            
            int written = write(parentToChild[1], data, sizeof(data));

            if (written == -1) {
                std::cout<< strerror(errno);
                exit(0);
            }

            int* childCountedSum = new int;
            int readBytes = read(childToParent[0], childCountedSum, sizeof(childCountedSum));

            //std::cout << "Parent got child counted sum: " << *childCountedSum << std::endl;

            subTotalOfWorkes[i] = *childCountedSum;

            //wait(NULL);

            /*const char* buffer = "asd";
            int size = strlen(buffer);
            
            */
            //int written = write(parentToChild[1], buffer, size+1);

            // no more workers needed
            if (isEnd)
                break;
        }

    }

    while(wait(NULL) > 0);

    for (int i=0;i< this->workers; i++) {
        //std::cout << subTotalOfWorkes[i] << std::endl;
        calculatedTotal += subTotalOfWorkes[i];
    }

    return calculatedTotal;
}
