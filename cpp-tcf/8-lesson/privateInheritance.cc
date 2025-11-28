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

// Derived class using private inheritance
class RobotDog : private Animal
{
private:
    std::string model;
    int batteryLevel = 100;

public:
    RobotDog(std::string m) : model(m) {}

    void walk()
    {
        std::cout << model << " starts walking like a dog.\n";
        move();         // Reuse Animal's public function (now private in RobotDog)
        batteryLevel -= 10;
        if (batteryLevel < 20)
            recharge();
    }

    void recharge()
    {
        std::cout << model << " is recharging its battery...\n";
        rest();         // Access Animal's protected function (still accessible)
        batteryLevel = 100;
        std::cout << model << " battery full again.\n";
    }

    void status()
    {
        std::cout << model << " status -> Battery: " << batteryLevel
                  << ", (Animal energy internal): hidden\n";
    }
};

// Main function
int main()
{
    RobotDog r1("RoboPup-3000");

    r1.status();
    r1.walk();      // Allowed -- RobotDog's own public method
    r1.recharge();  // Allowed -- RobotDog's own method

    // The following would cause compilation errors:
    // r1.move();       // Error: move() is private in RobotDog
    // r1.eat();        // Error: eat() is private in RobotDog
    // r1.energy = 50;  // Error: energy is protected and private in RobotDog
}