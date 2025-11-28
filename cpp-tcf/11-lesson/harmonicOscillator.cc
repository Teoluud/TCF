#include <iostream>
#include <cmath>
#include <memory>
#include "TCanvas.h"
#include "TGraph.h"
#include "TPad.h"
#include "TAxis.h"

class Particle
{
private:
    double m_x;
    double m_mass;
public:
    Particle(double pos, double vel, double acc, double mass);
    void printState() const;
    void setX(double x);
    double getX();
    double getMass();
};

void oscillator(double dt = 0.01, int simTime = 10)
{
    constexpr double A = 0.20;  // Amplitude
    constexpr double m = 0.10;  // Mass
    constexpr double k = 0.5;   // spring constant
    std::unique_ptr<Particle> part = std::make_unique<Particle>(A, 0., 0., m);
    std::cout << "Ho creato la particella:\n";
    part->printState();
    
    TGraph *gPos = new TGraph();
    TGraph *gVel = new TGraph();
    TGraph *gPotEn = new TGraph();
    TGraph *gKinEn = new TGraph();

    auto omega = [k,m](){ return std::sqrt(k/m); };
    double timePassed = 0;
    while (timePassed < simTime)
    {
        auto position = [A, omega](double t){ return A * std::cos(omega() * t); };
        part->setX(position(timePassed));
        gPos->AddPoint(timePassed, part->getX());

        auto velocity = [A, omega](double t){ return -A * omega() * std::sin(omega() * t); };
        gVel->AddPoint(timePassed, velocity(timePassed));

        auto potentialEnergy = [k](double x){ return 1./2. * k * x * x; };
        gPotEn->AddPoint(timePassed, potentialEnergy(part->getX()));

        auto kineticEnergy = [m](double v){ return 0.5 * m * v * v; };
        gKinEn->AddPoint(timePassed, kineticEnergy(velocity(timePassed)));

        timePassed += dt;
    }

    TCanvas *canvas = new TCanvas("oscillator", "x(t)", 800, 600);
    canvas->Divide(2,2);
    canvas->cd(1);
    gPos->SetTitle("x (t);t [s];x [m]");
    gPos->SetMarkerStyle(20);
    gPos->SetMarkerSize(0.4);
    gPos->Draw("AP");

    canvas->cd(2);
    gVel->SetTitle("v (t);t [s]; v [m/s]");
    gVel->SetMarkerStyle(20);
    gVel->SetMarkerSize(0.4);
    gVel->Draw("AP");

    canvas->cd(3);
    gPotEn->SetTitle("Potential Energy;t [s];U [J]");
    gPotEn->SetMarkerStyle(20);
    gPotEn->SetMarkerSize(0.4);
    gPotEn->Draw("AP");

    canvas->cd(4);
    gKinEn->SetTitle("Kinetic Energy;t [s];K [J]");
    gKinEn->SetMarkerStyle(20);
    gKinEn->SetMarkerSize(0.4);
    gKinEn->Draw("AP");
}

Particle::Particle(double pos, double vel, double acc, double mass) : m_x(pos), m_mass(mass) {}

void Particle::printState() const
{
    std::cout << "Position: (" << m_x << ") m\n";
    std::cout << "Mass: " << m_mass << " kg\n";
}

void Particle::setX(double x)
{
    m_x = x;
}

double Particle::getX() {return m_x;}

double Particle::getMass() {return m_mass;}