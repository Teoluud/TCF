#pragma once

template<typename T, int N>
class particleND
{
private:
    T m_position[N];
    T m_velocity[N];
    T m_mass;
public:
    particleND(const T pos[N], const T vel[N], T m);
    void printState() const;
    void updatePosition (double dt = 0.01);
};