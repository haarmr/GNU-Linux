#ifndef HEADERFILE_H
#define HEADERFILE_H

#include <string>

class ShellService
{
public:
    void start_shell();
    void split_str(std::string command, char** arr);
};

#endif
