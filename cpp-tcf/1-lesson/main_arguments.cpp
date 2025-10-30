#include <iostream>

int main(int argc, char ** argv)
{
    std::cout << "Input parameters from command line:" << std::endl;
    std::cout << "You decided to pass a string of " << argc << " parameters: " << std::endl;
    for (int i = 0; i < argc; i++)
        std::cout << "Parameter " << i+1 << ": " << argv[i] << std::endl;
    std::cout << "note that argv[" << argc << "] is a null pointer" << std::endl;
}