#include <iostream>

int main()
{
    int var = 5;
    std::cout << "Variable value: " << var++ << std::endl; //post-incremented -> var=6
    var >>= 1; // bitwise right-shift: 110 -> 011
    std::cout << "New value: " << --var << std::endl; //pre-decremented: var=2
    var %= 2;
    std::cout <<"Final value: " << var << std::endl;
}