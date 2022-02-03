#include "ComplexNumber.h"

using namespace Homework1;

ComplexNumber::ComplexNumber(int first, int second)
{
    real = first;
    imaginary = second;
}

ComplexNumber Homework1::operator+(ComplexNumber& a, const ComplexNumber& b)
{
    ComplexNumber c(a.real + b.real, a.imaginary + b.imaginary);

    return c;
}

int Homework1::ComplexNumber::GetReal()
{
    return real;
}

int Homework1::ComplexNumber::GetImaginary()
{
    return imaginary;
}