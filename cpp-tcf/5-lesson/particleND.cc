#pragma once

#include <iostream>
#include "particleND.h"

template<typename T, int N>
particleND<T,N>::particleND(const T pos[N], const T vel[N], T m) : m_mass(m)
{
    for (int i = 0; i < N; ++i) 
    {
        m_position[i] = pos[i];
        m_velocity[i] = vel[i];
    }
}

template<typename T, int N>
void particleND<T,N>::printState() const
{
    std::cout << "Position: (";
    for (int i = 0; i < N; i++) 
    {
        std::cout << m_position[i];
        if (i < N - 1) std::cout << ", ";
    }
    std::cout << "), Velocity: (";
    for (int i = 0; i < N; ++i) 
    {
        std::cout << m_velocity[i];
        if (i < N - 1) std::cout << ", ";
    }
    std::cout << "), Mass: " << m_mass << std::endl;
}

template<typename T, int N>
void particleND<T,N>::updatePosition(double dt)
{
    for (int i = 0; i < N; ++i)
    {
        m_position[i] += m_velocity[i]*dt;
    }
}

