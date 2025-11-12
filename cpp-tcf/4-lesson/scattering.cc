#include <iostream>
#include "scattering.h"

scattering::scattering(const particle2D & part1, const particle2D & part2, float l):
    m_part1 (part1),
    m_part2 (part2),
    m_l (l)
{
}


float scattering::checkDistanceSquared()
{
    float x1 = m_part1.getX();
    float y1 = m_part1.getY();
    float x2 = m_part2.getX();
    float y2 = m_part2.getY();
    float rSquared = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    return rSquared;
}

bool scattering::inSimulationArea(float xCenter, float yCenter)
{
    float xMax = xCenter + m_l / 2;
    float xMin = xCenter - m_l / 2;
    float yMax = yCenter + m_l / 2;
    float yMin = yCenter - m_l / 2;
    float x1 = m_part1.getX();
    float y1 = m_part1.getY();
    float x2 = m_part2.getX();
    float y2 = m_part2.getY();
    return (x1 < xMax && x1 > xMin && y1 < yMax && y1 > yMin && x2 < xMax && x2 > xMin && y2 < yMax && y2 > yMin);
}

particle2D * scattering::simulateInelasticScattering(double dr, double dt)
{
    particle2D * sumPart = nullptr;
    float distanceSquared = -666;
    float xC = (m_part1.getX() + m_part2.getX()) / 2;
    float yC = (m_part1.getY() + m_part2.getY()) / 2;
    while (true)
    {
        if (!inSimulationArea(xC, yC))
        {
            std::cout << "The particles did not scatter.\n";
            break; 
        }
        distanceSquared = checkDistanceSquared();
        if (distanceSquared <= dr*dr)
        {
            sumPart = new particle2D();
            *sumPart = m_part1 + m_part2;
            break;
        }
        m_part1.updatePosition(dt);
        m_part2.updatePosition(dt);
    }
    return sumPart;
}

scattering::~scattering()
{
}