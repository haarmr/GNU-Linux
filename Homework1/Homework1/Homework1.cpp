#include <iostream>
#include "ComplexNumber.h"

using namespace Homework1;

int main()
{
    ComplexNumber x(5, 10), y(50, 90), u(50, 70);
    ComplexNumber z = x + y + u;

   std::cout << "Real: " << z.GetReal() << ", Imaginary: " << z.GetImaginary();
}

