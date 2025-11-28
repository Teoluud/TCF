#include <iostream>

template <typename T>
T sum (T a, T b)
{
    return a + b ;
}

int main()
{
    int i_a = 3;

    int i_b = 5;

    float f_a = 3.2;

    float f_b = 4.5;

    std::cout << "sum of integers    " << sum (i_a, i_b) << std::endl ;

    std::cout << "sum of integers    " << sum<int> (i_a, i_b) << std::endl ; // telling the compiler that the type is an int

    std::cout << "sum of floats      " << sum (f_a, f_b) << std::endl ;
}