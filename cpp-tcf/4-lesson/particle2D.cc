#include <iostream>
#include "particle2D.h"

particle2D::particle2D (float x0, float y0, float vx0, float vy0, float m):
    m_x (x0),
    m_y (y0),
    m_vx (vx0),
    m_vy (vy0),
    m_mass (m)
{
}

particle2D::particle2D ():
    m_x (0.),
    m_y (0.),
    m_vx (0.),
    m_vy (0.),
    m_mass (0.)
{
}

particle2D::particle2D (float pos[2], float vel[2], float m):
    m_x (pos[0]),
    m_y (pos[1]),
    m_vx (vel[0]),
    m_vy (vel[1]),
    m_mass (m)
{
}

particle2D::particle2D (const particle2D & orig):
    m_x (orig.m_x),
    m_y (orig.m_y),
    m_vx (orig.m_vx),
    m_vy (orig.m_vy),
    m_mass (orig.m_mass)
{
}

particle2D::~particle2D()
{
}

void particle2D::printState() const
{
    std::cout << "Position: (" << m_x << ", " << m_y << ") m\n";
    std::cout << "Velocity: (" << m_vx << ", " << m_vy << ") m/s\n";
    std::cout << "Mass: " << m_mass << " kg\n";
}

particle2D particle2D::operator+ (const particle2D & merger)
{
    particle2D sum;

    sum.m_mass = m_mass + merger.m_mass;
    sum.m_vx = (m_mass * m_vx + merger.m_mass * merger.m_vx) / sum.m_mass;
    sum.m_vy = (m_mass * m_vy + merger.m_mass * merger.m_vy) / sum.m_mass;
    sum.m_x = (m_x + merger.m_x) / 2;
    sum.m_y = (m_y + merger.m_y) / 2;
    return sum;
}

void particle2D::updatePosition(double dt)
{
    m_x += m_vx * dt;
    m_y += m_vy * dt;
}

float particle2D::getX()
{
    return m_x;
}

float particle2D::getY()
{
    return m_y;
}

float particle2D::getVX()
{
    return m_vx;
}

float particle2D::getVY()
{
    return m_vy;
}

void particle2D::setVX(float vx)
{
    m_vx = vx;
}

void particle2D::setVY(float vy)
{
    m_vy = vy;
}