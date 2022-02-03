namespace Homework1
{
    class ComplexNumber
    {
    private:
        int real, imaginary;
    public:
        ComplexNumber(int first, int second);
        int GetReal();
        int GetImaginary();
        friend ComplexNumber operator+(ComplexNumber& a, const ComplexNumber& b);
    };

}