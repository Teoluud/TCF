#include <iostream>

class particle2D
{
public:
    particle2D (float x0, float y0, float vx0, float vy0, float m); // Constructor
    particle2D ();
    particle2D (float pos[2], float vel[2], float m);
    particle2D (const particle2D & orig); // Copy constructor
    particle2D operator+ (const particle2D & merger); // Sum operator
    ~particle2D (); // Destructor
    void printState() const; // Method to print state
    void updatePosition(double dt = 0.1);

    float getX();
    float getY();
    float getVX();
    float getVY();
    void setVX(float vx);
    void setVY(float vy);

private:
    float m_x, m_y; // Position
    float m_vx, m_vy; // Velocity
    float m_ax, m_ay; // Acceleration
    float m_mass;
};