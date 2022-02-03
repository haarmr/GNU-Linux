#include "Homework1.h"
#include <iostream>

using namespace Homework1;
using namespace std;

int main()
{
    ComplexNumber x(5, 10), y(50, 90);

    ComplexNumber z = x + y;

    cout << "Real: "<< z.real << ", Imaginary: " << z.imaginary;
}

