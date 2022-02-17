#include "IPCService.h"
#include <iostream>
#include <sys/types.h>
#include <unistd.h> 
#include <string.h>
#include <sys/wait.h> 
#include <math.h> 

/*
 * Create array of given size and fill with random data
 */
IPCService::IPCService(int arraySize, int workers)
{
    // set data
    this->workers = workers;
    this->arraySize = arraySize;

    // create array of size
    this->myArray = new int[this->arraySize];
    
    // fill random data
    for (int i=0;i<this->arraySize;i++){
        myArray[i] = rand() % 1000;
    }
}

/*
 * Calculate sum of array
 */
int IPCService::sum_synchron()
{
    int sum=0;

    // iterate throught each data
    for(int i=0;i<this->arraySize;i++) {

        // add to sum
        sum += this->myArray[i];
    }

    // return total
    return sum;
}

/*
 * Calculate sum with child proccesses
 */
int IPCService::calculate_sum()
{
    // find how mamny indexes of array each proccess can carry
    int eachWorkerStrength = ceil((float) this->arraySize/this->workers);

    // create array to store each workers calculated sum
    int *subTotalOfWorkes = new int[this->workers];

    // true when array last element reached
    bool isEnd = false;

    int calculatedTotal = 0;

    // child to parent pipes array
    int **childToParentPipes = new int*[this->workers];

    // create workers
    for (int i=0; i < this->workers; i++) {

        // child only read from parent
        int parentToChild[2];

        // child only write to parent
        int* childToParent = new int[2];
    
        // create pipes for comunicating between parent and child proccesses
        pipe(parentToChild);
        pipe(childToParent);

        childToParentPipes[i] = childToParent;
        
        // create child
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
        
            // buffer to store bytes read
            int *data = new int[2];

            // read bytes from pipe
            int readBytes = read(parentToChild[0], data, sizeof(data));

            // create int in heap for passing to parent
            int* childCountedSum = new int();

            // calculate given part of the array
            for (int j=data[0]; j<data[1]; j++) {
                *childCountedSum += this->myArray[j];
            }
          
            // send sum to parent
            int written = write(childToParent[1], childCountedSum, sizeof(childCountedSum));

            // make sure data has been sent
            if (written == -1) {
                std::cout<< strerror(errno);
                exit(0);
            }

            // exit to prevent chil to enter out loop and start another childs
            exit(0);
        }
        else {

            // close unused pipes
            close(parentToChild[0]);
            close(childToParent[1]);

            // get each worker starting index
            int workerStartIndex = i*eachWorkerStrength;

            // get each worker ending index
            int workerEndIndex = workerStartIndex + eachWorkerStrength;

            // make sure end index is the array size
            if (workerEndIndex >= this->arraySize) {
            
                // set end index to last index
                workerEndIndex = this->arraySize;

                // end of the array reached
                isEnd = true;
            }

            // create data store in heap to send to child
            int* data = new int[2];
            data[0] = workerStartIndex;
            data[1] = workerEndIndex;

            // send data to child           
            int written = write(parentToChild[1], data, sizeof(data));

            // make sure data sent
            if (written == -1) {
                std::cout<< strerror(errno);
                exit(0);
            }

            

            // no more workers needed
            if (isEnd)
                break;
        }
    }


    // read from each worker pipe   
    for (int i=0; i < this->workers; i++) {

        int *childToParent = new int[2];

        childToParent = childToParentPipes[i];

        // create buffer to write the bytes read
        int* childCountedSum = new int;

        // read from pipe
        int readBytes = read(childToParent[0], childCountedSum, sizeof(childCountedSum));

        // add worker counted sum to array
        subTotalOfWorkes[i] = *childCountedSum;
    }

    // wait for all workers to finish
    while(wait(NULL) > 0);

    // calculate total sum of workers counted
    for (int i=0;i< this->workers; i++) {
        calculatedTotal += subTotalOfWorkes[i];
    }

    // return sum
    return calculatedTotal;
}
