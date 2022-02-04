#include <iostream>
#include "ComplexNumber.h"

using namespace Homework1;

int main()
{
    // define complex numbers
    ComplexNumber x(5, 10), y(5, 5), u(50, 70), f(44, 99);

    // count 
    ComplexNumber z = x * y - u;

    // print absolute value of complex number
    std::cout << "Absolute value: " << abs(z) << "\n";

    // print real and imaginary number of complex number
    std::cout << "Real: " << z.GetReal() << ", Imaginary: " << z.GetImaginary() << std::endl;

    // create array of complex numbers
    ComplexNumber arr[5] = { x, y, u, z, f };

    // print unsorted array 
    for (int i = 0; i < 5; i++) {
        std::cout << abs(arr[i]) << "\t";
    }
    std::cout<< "\n";

    // implement bubble sorting algorithm
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (abs(arr[j]) < abs(arr[i])) {

                ComplexNumber temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    // print sorted array
    for (int i = 0; i < 5; i++) {
        std::cout << abs(arr[i]) << "\t";
    }
}

