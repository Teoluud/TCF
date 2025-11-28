#include <iostream>

double decay(double nAtoms, int nHalfLives)
{
    //std::cout << nAtoms << std::endl;
    if (nHalfLives == 1) return (nAtoms / 2);
    else return (decay(nAtoms, nHalfLives - 1) / 2);
}

int main()
{
    double atoms = 6.02214076e23;
    
    std::cout << "Number of atoms after 10 half lives: " << decay(atoms, 10) << std::endl;
}