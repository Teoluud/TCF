#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

int main()
{
    vector<double> velocities = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};

    double sum = 0.0;
    // Using iterator
    for (vector<double>::const_iterator it = velocities.begin(); it != velocities.end(); ++it) // or:  for (double v : velocities)
    {
        sum += *it;
    }

    double average = sum / velocities.size();

    string message = "The average is: " + to_string(average) + " m/s";

    cout << message << endl;

    // Map exercise
    map <string, double> particleMasses = {{"electron", 0.511}, {"proton", 938.272}, {"neutron", 939.565}};

    string particle;
    cout << "Choose particle: ";
    cin >> particle;

    string output = "The mass of the " + particle + " is " + to_string(particleMasses[particle]) + " MeV / c^2.";

    cout << output << endl;
}