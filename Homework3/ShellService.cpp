#include "ShellService.h"
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string>

using namespace std;

/*
 * Method to split provided string by space and store into array
 */
void ShellService::split_str(string command, char** next)
{
    // define required data
    char *temp = NULL;
    char *dupCommand = strdup(command.c_str());
    
    // split string by space
    temp = strtok(dupCommand, " ");

    // iterate on each word until end
    while (temp != NULL)
    {
        // store into array
        *next++ = temp;

        // go to next word
        temp = strtok(NULL, " ");
    }
 
    // set last arg to NULL
    *next = NULL;
}

/* 
 * Open shell in console
 */
void ShellService::start_shell() 
{
    // string to store passed data
    string command;
    
    while(true) {

        //Define the dynamic array variable of string
        char *args[20];
        char **next = args;

        cout << "$ ";

        // get input from user
        getline(cin, command);   
        
        // make sure exit not required
        if (command == "exit") 
            break;

        cout << "Executing command: " << command << endl;

        // split string by space into array 
        this->split_str(command, next);

        // start child proccess
        pid_t child = fork();

        // make sure child proccess started
        if (child == -1) {
            cout << strerror(errno);
            exit(errno);
        }

        // separate child logic from parent, child is 0 in child procces
        if (child == 0) {

            // get pid of child procces
            pid_t pid = getpid();

            // define direcotry for proccess` std files
            string fileDir = "/opt/silentshell/" + to_string(pid);

            // make direcotry if not exists
            mkdir(fileDir.c_str() , 0777);

            // define std file names
            string inputFile = fileDir + "/in.std";
            string outFile = fileDir + "/out.std";
            string errFile = fileDir + "/err.std";

            // open new stdin file
            int fdIn = open(inputFile.c_str(), O_RDWR|O_CREAT|O_APPEND, 0600);
            int fdOut = open(outFile.c_str(), O_RDWR|O_CREAT|O_APPEND, 0600);
            int fdErr = open(errFile.c_str(), O_RDWR|O_CREAT|O_APPEND, 0600);

            // close existing file and assign descriptore to our new variables
            dup2(fdIn, 0);
            dup2(fdOut, 1);
            dup2(fdErr, 2);

            // execute command expecting std files in our new directory for proccess
            execvp(args[0], args);

            // exit child
            return;
        } 
        else {

            // wait for the child to finish
            wait(&child);
        }
    }

    cout << "Closing shell" << endl;

}