#include <iostream>
#include <TGraph.h>
#include <TCanvas.h>
#include <TAxis.h>

float compute_acceleration(float k, float mass, float position);

void update_velocity(float &velocity, float acceleration, float time_step);

void update_position(float *position, float velocity, float time_step);

int main()
{
    float mass = 2.0; // mass in kg
    float k = 10.0;   // spring constant in N/m
    float x0 = 0.5;  // initial displacement in m
    float v0 = 0.0;  // initial velocity in m/s
    float dt = 0.01;  // time step in s
    int steps = 1000; // number of time steps

    float *acceleration_array = new float [steps];
    float *velocity_array = new float [steps];
    float *position_array = new float [steps];
    float *time_array = new float [steps];

    float time = 0;
    float position = x0;
    float velocity = v0;
    float acceleration = compute_acceleration(k, mass, position);
    acceleration_array[0] = acceleration;
    velocity_array[0] = velocity;
    position_array[0] = position;
    time_array[0] = time;
    
    for (int i = 1; i < steps; i++)
    {
        acceleration = compute_acceleration(k, mass, position);
        update_velocity(velocity, acceleration, dt);
        update_position(&position, velocity, dt);
        time += dt;

        acceleration_array[i] = acceleration;
        velocity_array[i] = velocity;
        position_array[i] = position;
        time_array[i] = time;
        
        // std::cout << position << std::endl;
        
    }
    
    TCanvas *canvas = new TCanvas("oscillator", "x(t)", 1080, 720);
    TGraph *grafico = new TGraph(steps, time_array, position_array);
    grafico->GetXaxis()->SetTitle("t [s]");
    grafico->GetYaxis()->SetTitle("x [m]");
    grafico->SetTitle("x (t)");
    grafico->Draw("AP");

    canvas->SaveAs("graph.png");

    delete [] acceleration_array;
    delete [] velocity_array;
    delete [] position_array;
    delete [] time_array;
    delete canvas;
    delete grafico;
}

float compute_acceleration(float k, float mass, float position)
{
    return - (k * position) / mass;
}

void update_velocity(float &velocity, float acceleration, float time_step)
{
    velocity += acceleration * time_step;
}

void update_position(float *position, float velocity, float time_step)
{
    *position += velocity * time_step;
}