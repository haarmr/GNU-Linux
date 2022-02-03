#include "ComplexNumber.h"

using namespace Homework1;

ComplexNumber::ComplexNumber(int first, int second)
{
    real = first;
    imaginary = second;
}


int ComplexNumber::GetReal()
{
    return real;
}

int ComplexNumber::GetImaginary()
{
    return imaginary;
}

ComplexNumber Homework1::operator-(ComplexNumber a, const ComplexNumber& b)
{
    ComplexNumber c(a.real - b.real, a.imaginary - b.imaginary);

    return c;
}

ComplexNumber Homework1::operator + (ComplexNumber a, const ComplexNumber& b)
{
    ComplexNumber c(a.real + b.real, a.imaginary + b.imaginary);

    return c;
}
