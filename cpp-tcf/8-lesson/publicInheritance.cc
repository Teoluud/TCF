#include <iostream>
#include <string>

// Base class
class Animal
{
public:
    std::string name;

    // Constructor
    Animal(std::string n) : name(n) {}

    // Public function - part of the base interface
    void eat() { std::cout << name << " is eating.\n"; }

protected:
    int energy = 100; // Protected member - accessible to derived classes, not to main()

    void rest() // Protected method - same rule
    {
        energy += 10;
        std::cout << name << " is resting. Energy now: " << energy << "\n";
    }
};

// Derived class (public inheritance)
class Dog : public Animal
{
public:
    std::string breed;

    // Constructor - calls base constructor
    Dog(std::string n, std::string b) : Animal(n), breed(b) {}

    // New function specific to dog
    void fetch()
    {
        if (energy >= 20) // Accessing protected member from base
        {
            std::cout << name << " the " << breed << " is fetching the ball!\n";
            energy -= 20;
        }
        else
        {
            std::cout << name << " is too tired to fetch.\n";
            rest();         // Accessing protected function from base
        }
    }
};

// Main function
int main()
{
    Dog d("Fido", "Labrador");

    // Access base class public function
    d.eat();

    // Access derived class public function
    d.fetch();

    // I cannot call:
    // d.energy = 50;
}