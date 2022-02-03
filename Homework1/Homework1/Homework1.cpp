#include <iostream>
#include "ComplexNumber.h"

using namespace Homework1;

int main()
{
    ComplexNumber x(5, 10), y(50, 90);
    ComplexNumber z = x + y;

   std::cout << "Real: " << z.GetReal() << ", Imaginary: " << z.GetImaginary();
}

