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

void split_strrr(string command, char** next)
{
    char *temp = NULL;
    char *dupCommand = strdup(command.c_str());
    
    temp = strtok(dupCommand, " ");

    while (temp != NULL)
    {
        *next++ = temp;
        temp = strtok(NULL, " ");
    }
 
    // set last arg to NULL
    *next = NULL;

   
    //return next;
}

void ShellService::start_shell() 
{

    string command;
    
    while(true) {

        //Define the dynamic array variable of string
        char *args[20];
        char **next = args;

        cout << "$ ";
        getline(cin, command);   
        
        if (command == "exit") 
            break;

        cout << "Executing command: " << command << endl;

        split_strrr(command, next );

        pid_t child = fork();

        if (child == -1) {
            cout << strerror(errno);
            exit(errno);
        }

        if (child == 0) {

            pid_t pid = getpid();
            string fileDir = "/opt/silentshell/" + to_string(pid);

            mkdir(fileDir.c_str() , 0777);
            string inputFile = fileDir + "/in.std";
            string outFile = fileDir + "/out.std";
            string errFile = fileDir + "/err.std";

            // open stdin file
            int fdIn = open(inputFile.c_str(), O_RDWR|O_CREAT|O_APPEND, 0600);
            int fdOut = open(outFile.c_str(), O_RDWR|O_CREAT|O_APPEND, 0600);
            int fdErr = open(errFile.c_str(), O_RDWR|O_CREAT|O_APPEND, 0600);

            dup2(fdIn, 0);
            dup2(fdOut, 1);
            dup2(fdErr,2);

            execvp(args[0], args);

            return;
        } 
        else {

            wait(&child);
        }
        
    }

    cout << "Closing shell" << endl;

}