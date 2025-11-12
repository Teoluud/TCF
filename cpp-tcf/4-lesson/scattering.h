#include "particle2D.h"

class scattering
{
private:
    particle2D m_part1;
    particle2D m_part2;
    float m_l;

public:
    scattering (const particle2D & part1, const particle2D & part2, float l);
    //scattering (float pos1[2], float vel1[2], float pos2[2], float vel2[2]);
    ~scattering ();
    bool inSimulationArea(float xCenter, float yCenter);
    float checkDistanceSquared();
    particle2D * simulateInelasticScattering(double dr = 0.1, double dt = 0.1);
};