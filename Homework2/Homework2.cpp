#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>  
#include <string.h>
#include <cstdlib>
#include <cstdio>

using namespace std;


void print_file_size (int file) 
{
    int offset = 0;
    int logicalSize = 0;
    int physicalSize = 0;

    while (true) {

        // try jump to next beginning of hole
        off_t data = lseek(file, offset, SEEK_HOLE);

        // there was some data if we got to next hole
        if(data > 0){

            // set sizes
            logicalSize = data;
            physicalSize += data - offset;

            // move pointer
            offset = data;
        }

        // reached the end of file
        if(data == 0){
            break;
        }

        // something went wrong
        if(data < 0){
            std::cerr << "Something went wrong. " << strerror(errno) << std::endl;
            exit(errno);
        }

        // try find next data jumping over a hole
        off_t hole = lseek(file, offset, SEEK_DATA);

        // reached the end no data to read
        if(hole == -1 && errno == ENXIO){
            break;
        }

        // something went wrong
        if(hole == -1){
            std::cerr << "Something went wrong. " << strerror(errno) << std::endl;
            exit(errno);
        }

        if(hole > 0){

            // move pointer
            offset = hole;

            // if hole exists then add size to logical file size
            logicalSize += hole - data;
        }
    }

    cout << "Logical size: " << logicalSize << endl;
    cout << "Physical size: " << physicalSize << endl;
}


int main(int argc, char *argv[])
{
    extern int errno;
    // check if all parameters are passed
    if (argc < 3){
        cout << "Missing parameter";
        return 0;
    }

    int sourceFile = open(argv[1], O_RDONLY);

    // check if opened success
    if (sourceFile == -1) {
        cout << "Unable to open source file, exiting" << endl;
        return errno;
    }

    cout << "Printing sizes of source file" << endl;
    
    // file size information of source file
    print_file_size(sourceFile);

    cout << endl;
    // open destintation file
    int destFile = open(argv[2], O_CREAT | O_RDWR, 0777);

    // check if opened success
    if (destFile == -1) {
        cout << strerror(errno) <<endl;
        return errno;
    }

    // set pointer to start
    int offset = 0;

    // start copy process
    while (true) {

        // try jump to next beginning of hole
        off_t data = lseek(sourceFile, offset, SEEK_HOLE);

        // there was some data if we got to next hole
        if(data > 0){
            std::cout << "Data Area Detected from " << offset << " to " <<  data << std::endl;
        }

        // reached the end of file
        if(data == 0){
            break;
        }

        // something went wrong
        if(data < 0){
            std::cerr << "Something went wrong. " << strerror(errno) << std::endl;
            exit(errno);
        }

        char buff[data-offset];

        cout << "Read: " << data-offset << "  of data" <<endl;

        // move the pointer to the offset to again start reading 
        lseek(sourceFile, offset, SEEK_SET);

        // read the data from the offset
        int bytesRead = read(sourceFile, buff, data-offset); 

        cout << "Write: " << bytesRead << "  of data" <<endl;

        write(destFile, buff, bytesRead);

        // change offset to end of data just read
        offset = data;
        
        // try find next data jumping over a hole
        off_t hole = lseek(sourceFile, offset, SEEK_DATA);

        // reached the end no data to read
        if(hole == -1 && errno == ENXIO){
            break;
        }

        // something went wrong
        if(hole == -1){
            std::cerr << "Something went wrong. " << strerror(errno) << std::endl;
            exit(errno);
        }

        if(hole > 0){
            
            // create next portion
            off_t holeCreated = lseek(destFile, hole-offset, SEEK_END);

            // could not create a hole for some reason
            if(holeCreated < 0){
                std::cerr << "Could not create a hole with size " << " because of error " << strerror(errno) << std::endl;
                break;
            }

            // move pointer
            offset = hole;
        }

    }

    cout << endl;
    
    // file size information of destination file
    print_file_size(destFile);

    return 0;
}

