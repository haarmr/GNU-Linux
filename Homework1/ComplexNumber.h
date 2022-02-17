#ifndef HEADERFILE_H
#define HEADERFILE_H

class ComplexNumber
{
private:
    int real;
    int imaginary;
public:
    ComplexNumber(int real, int imaginary);
    int get_real();
    int get_imaginary();
    int get_absolute();
    friend ComplexNumber operator - (ComplexNumber first, const ComplexNumber& second);
    friend ComplexNumber operator + (ComplexNumber first, const ComplexNumber& second);
    friend ComplexNumber operator * (ComplexNumber first, const int second);
};

#endif
