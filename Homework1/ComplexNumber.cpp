#include "ComplexNumber.h"
#include <cmath>

/**
 * Init values on construct
 */
ComplexNumber::ComplexNumber(int real, int imaginary)
{
    this->real = real;
    this->imaginary = real;
}

/**
 * Return real number of complex
 */
int ComplexNumber::get_real()
{
    return this->real;
}

/**
 * Return imaginary number of complex
 */
int ComplexNumber::get_imaginary()
{
    return this->imaginary;
}

/**
 * Overload substract(-) operator for complex
 */
ComplexNumber operator-(ComplexNumber a, const ComplexNumber& b)
{  
    a.real -= b.real;
    a.imaginary -= b.imaginary;

    return a;
}

/**
 * Overload add(+) operator for complex
 */
ComplexNumber operator + (ComplexNumber a, const ComplexNumber& b)
{
    a.real += b.real;
    a.imaginary += b.imaginary;

    return a;
}

/**
 * Overload miltiply(*) operator for complex
 */
ComplexNumber operator * (ComplexNumber a, const ComplexNumber& b)
{
    a.real *= b.real;
    a.imaginary *= b.imaginary;

    return a;
}

/**
 * Overload absolute value calculation method for complex
 */
int ComplexNumber::get_absolute()
{
    // count absolute value
    int absoluteValue = sqrt(pow(this->real,2) + pow(this->imaginary, 2));

    return absoluteValue;
}

