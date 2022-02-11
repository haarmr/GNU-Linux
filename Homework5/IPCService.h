#ifndef HEADFILE_H
#define HEADFILE_H

class IPCService
{
    private:
        int arraySize;
        int workers;
        int *myArray;
    
    public:
        IPCService(int arraySize, int workers);
        void calculate_sum();
        int sum_synchron();

};

#endif
