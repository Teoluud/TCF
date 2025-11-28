#include <iostream>
#include <string>

// Base class
class Animal
{
public:
    void move()
    {
        std::cout << "Animal is moving...\n";
    }
    
    void eat()
    {
        std::cout << "Animal is eating...\n";
    }

protected:
    int energy = 100;

    void rest()
    {
        energy += 10;
        std::cout << "Animal resting. Energy now: " << energy << "\n";
    }
};

// Derived class using protected inheritance
class DogTrainer : protected Animal
{
private:
    std::string trainerName;

public:
    DogTrainer(std::string name) : trainerName(name) {}

    void trainDog()
    {
        std::cout << trainerName << " starts dog training.\n";
        move();         // OK: public in Animal -> protected in DogTrainer
        energy -= 20;
        rest();         // OK: protected in Animal -> protected in DogTrainer
        std::cout << "Training session done. Trainer's animal energy: " << energy << "\n";
    }

protected:
    void takeBreak()
    {
        std::cout << trainerName << " takes a break with the animals.\n";
        rest();
    }
};

// Derived class of DogTrainer (second level)
class SeniorTrainer : public DogTrainer
{
public:
    SeniorTrainer(std::string name) : DogTrainer(name) {}

    void conductAdvancedSession()
    {
        std::cout << "Senior trainer conducts an advanced training session.\n";
        trainDog();     // Accessible (protected in base)
        takeBreak();    // Accessible (protected in base)
    }
};

// Main
int main()
{
    DogTrainer trainer("Alex");
    trainer.trainDog(); // Accessible (public method in DogTrainer)

    // These cause compilation errors:
    // trainer.move();  // Error: move() became protected
    // trainer.eat();   // Error: eat() became protected
    // trainer.rest();  // Error: rest() is protected
    // trainer.energy();    // Error: energy is protected

    SeniorTrainer senior("Morgan");
    senior.conductAdvancedSession(); // Allowed
}