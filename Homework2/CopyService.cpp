#include "CopyService.h"
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>  
#include <string.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>

CopyService::CopyService()
{

}

/*
 * Prints the logical and physical sizes of the specified file
 */
void CopyService::print_file_size(int fileDescriptor)
{
    // set initial data
    int offset = 0;
    int logicalSize = 0;
    int physicalSize = 0;

    while (true) {

        // try jump to next beginning of hole
        off_t data = lseek(fileDescriptor, offset, SEEK_HOLE);

        // there is some data if we got to next hole
        if(data > 0){

            // set sizes
            logicalSize = data;
            physicalSize += data - offset;

            // move pointer
            offset = data;
        }

        // something went wrong
        if(data < 0){
            std::cout << "Something went wrong. " << strerror(errno) << std::endl;
            exit(errno);
        }

        // try find next data jumping over a hole
        off_t hole = lseek(fileDescriptor, offset, SEEK_DATA);

        // reached the end no data to read
        if(hole == -1 && errno == ENXIO){
            break;
        }

        // something went wrong
        if(hole == -1){
            std::cerr << "Something went wrong. " << strerror(errno) << std::endl;
            exit(errno);
        }

        // there is some hole if we got to next data
        if(hole > 0){

            // move pointer
            offset = hole;

            // if hole exists then add size to logical file size
            logicalSize += hole - data;
        }
    }

    std::cout << "Logical size: " << logicalSize << std::endl;
    std::cout << "Physical size: " << physicalSize << std::endl;
}

/* 
 * Copy source file with holes to destination 
 */
void CopyService::copy_file(int sourceFileDescriptor, int destFileDescriptor)
{
    // set pointer to start
    int offset = 0;

    // start copy process
    while (true) {

        // try jump to next beginning of hole
        off_t data = lseek(sourceFileDescriptor, offset, SEEK_HOLE);

        // there was some data if we got to next hole
        if(data > 0){
            std::cout << "Data Area Detected from " << offset << " to " <<  data << std::endl;

            char buff[data-offset];

            std::cout << "Read: " << data-offset << "  of data" << std::endl;

            // move the pointer to the offset to again start reading 
            lseek(sourceFileDescriptor, offset, SEEK_SET);

            // read the data from the offset
            int bytesRead = read(sourceFileDescriptor, buff, data-offset); 

            std::cout << "Write: " << bytesRead << "  of data" << std::endl;

            write(destFileDescriptor, buff, bytesRead);

            // change offset to end of data just read
            offset = data;
        }

        // something went wrong
        if(data < 0){
            std::cerr << "Something went wrong. " << strerror(errno) << std::endl;
            exit(errno);
        }
        
        // try find next data jumping over a hole
        off_t hole = lseek(sourceFileDescriptor, offset, SEEK_DATA);

        // reached the end no data to read
        if(hole == -1 && errno == ENXIO){
            std::cerr << "reached the end no data to read" << std::endl;
            break;
        }

        // something went wrong
        if(hole == -1){
            std::cerr << "Something went wrong. " << strerror(errno) << std::endl;
            exit(errno);
        }

        if(hole > 0){
            
            // create next portion
            off_t holeCreated = lseek(destFileDescriptor, hole-offset, SEEK_END);

            // could not create a hole for some reason
            if(holeCreated < 0){
                std::cerr << "Could not create a hole with size " << " because of error " << strerror(errno) << std::endl;
                break;
            }

            // move pointer
            offset = hole;
        }
    }
}