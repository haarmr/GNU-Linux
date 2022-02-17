#ifndef HEADFILE_H
#define HEADFILE_H

class CopyService 
{
public:
    CopyService();
    void print_file_size(int fileDescriptor);
    void copy_file(int sourceFileDescriptor, int destFileDescriptor);
};

#endif
