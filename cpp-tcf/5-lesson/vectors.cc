#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = {1, 2, 3, 4};

    // Accessing using operator[]
    std::cout << "Element at index 1 using []: " << v[1] << std::endl;

    // Accessing using at()
    std::cout << "Element at index 3 using at(): " << v.at(3) << std::endl;

    // Uncommenting the next line will throw an out_of_range exception
    // std::cout << v.at(10) << std::endl;
}