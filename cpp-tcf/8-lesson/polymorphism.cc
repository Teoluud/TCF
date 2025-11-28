#include <iostream>

// Base class
class Animal
{
public:
    // Virtual function for polymorphism
    virtual void makeNoise() const
    {
        std::cout << "Some generic animal sound!\n";
    }

    // Virtual destructor (important for proper cleanup via base pointer)
    virtual ~Animal()
    {
        std::cout << "Animal destroyed\n";
    }
};

// Derived class: Dog
class Dog: public Animal
{
public:
    void makeNoise() const override
    {
        std::cout << "Woof! Woof!\n";
    }

    ~Dog()
    {
        std::cout << "Dog destroyed\n";
    }
};

// Derived class: Cat
class Cat : public Animal
{
public:
    void makeNoise() const override
    {
        std::cout << "Meow!\n";
    }

    ~Cat()
    {
        std::cout << "Cat destroyed\n";
    }
};

int main()
{
    // Base class pointer
    Animal* animal1 = new Dog();
    Animal* animal2 = new Cat();

    // Polymorphic behavior
    animal1->makeNoise();   // Output: Woof! Woof!
    animal2->makeNoise();   // Output: Meow!

    //Clean up
    delete animal1;     // Calls Dog's destructor, then Animal's
    delete animal2;     // Calls Cat's destructor, then Animal's
}