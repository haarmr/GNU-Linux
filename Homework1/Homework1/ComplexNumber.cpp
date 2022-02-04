#include "ComplexNumber.h"
#include <cmath>


// init values on construct
ComplexNumber::ComplexNumber(int first, int second)
{
    real = first;
    imaginary = second;
}

// return real number of complex
int ComplexNumber::GetReal()
{
    return real;
}

// return imaginary number of complex
int ComplexNumber::GetImaginary()
{
    return imaginary;
}

// overload substract(-) operator for complex
ComplexNumber operator-(ComplexNumber a, const ComplexNumber& b)
{
    a.real -= b.real;
    a.imaginary -= b.imaginary;

    return a;
}

// overload add(+) operator for complex
ComplexNumber operator + (ComplexNumber a, const ComplexNumber& b)
{
    a.real += b.real;
    a.imaginary += b.imaginary;

    return a;
}

// overload miltiply(*) operator for complex
ComplexNumber operator * (ComplexNumber a, const ComplexNumber& b)
{
    a.real *= b.real;
    a.imaginary *= b.imaginary;

    return a;
}

// overload absolute value calculation method for complex
int abs(ComplexNumber a)
{
    int absoluteValue = sqrt(pow(a.real,2) + pow(a.imaginary, 2));

    return absoluteValue;
}

