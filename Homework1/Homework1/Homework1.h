#include "complex"

using namespace std;

namespace Homework1
{
    class ComplexNumber
    {
    public:
        int real, imaginary;
        ComplexNumber(int first, int second)
        {
            real = first;
            imaginary = second;
        }
    };


    ComplexNumber operator+(ComplexNumber first, const ComplexNumber& second) {
    
        ComplexNumber c(first.real + second.real, first.imaginary + second.imaginary);

        return c;
    }

}