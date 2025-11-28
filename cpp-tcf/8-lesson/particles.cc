#include <iostream>
#include <string>

class Particle
{
protected:
    std::string m_name;
    double m_mass;

public:
    Particle(std::string name, double mass) : m_name(name), m_mass(mass) {}
    ~Particle() {}
    virtual void printInfo() const
    {
        std::cout << "Particle name: " << m_name << ", mass: " << m_mass << " MeV/c^2\n";
    }
    virtual void printCharge() const = 0;
};

class Lepton : public Particle
{
protected:
    double m_spin;

public:
    Lepton(std::string name, double mass, double spin) : Particle(name, mass), m_spin(spin) {}
    ~Lepton() {}
    void printInfo() const override
    {
        std::cout << "Lepton name: " << m_name
                  << ", mass: " << m_mass << " MeV/c^2"
                  << ", spin: " << m_spin << "\n";
    }
};

class Electron : public Lepton
{
public:
    Electron(std::string name) : Lepton(name, 0.511, 1/2) {}
    ~Electron() {}
    void printInfo() const override
    {
        std::cout << "Electron name: " << m_name
                  << ", mass: " << m_mass << " MeV/c^2"
                  << ", spin: 1/2\n";
    }
    void printCharge() const override
    {
        std::cout << "Electron charge: -e\n";
    }
};

class Muon : public Lepton
{
public:
    Muon(std::string name) : Lepton(name, 106., 1/2) {}
    ~Muon() {}
    void printInfo() const override
    {
        std::cout << "Muon name: " << m_name
                  << ", mass: " << m_mass << " MeV/c^2"
                  << ", spin: 1/2\n";
    }
    void printCharge() const override
    {
        std::cout << "Muon charge: -e\n";
    }
};

int main()
{
    Particle *part1 = new Electron("electron");

    Particle *part2 = new Muon("muon");    

    part1->printInfo();

    part2->printInfo();    

    part1->printCharge();

    part2->printCharge();

    delete part1;
    delete part2;
}