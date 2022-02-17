#include "ComplexNumber.h"
#include <iostream>

using namespace std;

int main()
{
    // define complex numbers
    ComplexNumber x(5, 10), y(5, 5), u(50, 70), f(44, 99);

    // count 
    ComplexNumber z = x * 5 - u;

    // print absolute value of complex number
    cout << "Absolute value: " << z.get_absolute() << "\n";

    // print real and imaginary number of complex number
    cout << "Real: " << z.get_real() << ", Imaginary: " << z.get_imaginary() << endl;

    // create array of complex numbers
    ComplexNumber arr[5] = { x, y, u, z, f };

    // print unsorted array 
    for (int i = 0; i < 5; i++) {
        std::cout << arr[i].get_absolute() << "\t";
    }
    cout<< "\n";

    // implement bubble sorting algorithm
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (arr[j].get_absolute() < arr[i].get_absolute()) {

                ComplexNumber temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    // print sorted array
    for (int i = 0; i < 5; i++) {
        cout << arr[i].get_absolute() << "\t";
    }
}

