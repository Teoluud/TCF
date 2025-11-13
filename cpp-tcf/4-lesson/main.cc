//#include "particle2D.h"
#include "scattering.h"

int main()
{
    particle2D *particleA = new particle2D(0., 0., 1., 0., 1.);
    particle2D *particleB = new particle2D(5., 0., 0., 0., 1.);
    float simulationLimit = 100.;
    scattering scatter (particleA, particleB, simulationLimit);
    particle2D *resultParticle = scatter.simulateInelasticScattering();
    if (resultParticle != nullptr)
        resultParticle->printState();
    else
    {
        particleA->printState();
        particleB->printState();
    }
    delete resultParticle;
    delete particleA;
    delete particleB;
}