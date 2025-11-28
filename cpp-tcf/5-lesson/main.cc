#include "particleND.h"

int main()
{
    const int dimensions = 3; // has to be const.
    float position[dimensions] = {0.0,0.0,0.0};
    float velocity[dimensions] = {3.0,2.0,1.0};
    float mass = 139.6; // MeV/c

    particleND<float,dimensions> part_pion(position,velocity,mass);

    part_pion.printState();

    int steps = 1000;
    for (int t = 0; t < steps; ++t)
        part_pion.updatePosition();
    
    part_pion.printState();
}