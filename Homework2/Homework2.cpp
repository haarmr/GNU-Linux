#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>  
#include <string.h>
#include <cstdlib>
#include <cstdio>
#include "CopyService.h"

using namespace std;

int main(int argc, char *argv[])
{
    // check if all parameters are passed
    if (argc < 3){
        cout << "Missing parameter";
        return 0;
    }

    // copy service instance
    CopyService cpService;

    // open source file specified
    int sourceFile = open(argv[1], O_RDONLY);

    // check if opened success
    if (sourceFile == -1) {
        cout << "Unable to open source file, exiting" << endl;
        return errno;
    }
    
    cout << "Printing sizes of source file" << endl;
    
    // file size information of source file
    cpService.print_file_size(sourceFile);
    
    // open destintation file
    int destFile = open(argv[2], O_CREAT | O_RDWR, 0777);

    // check if opened success
    if (destFile == -1) {
        cout << strerror(errno) <<endl;
        return errno;
    }

    // copy source file to destination
    cpService.copy_file(sourceFile, destFile);

    std::cout << "Printing sizes of destination file" << std::endl;

    // file size information of destination file
    cpService.print_file_size(destFile);

    return 0;
}

