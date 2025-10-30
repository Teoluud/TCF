#include "datanalysis.h"
#include <iostream>

void wavg(float data[], float errors[], int length)
{
    float weight = 0;
    float num = 0;
    for (int i = 0; i < length; i++)
    {
        weight += (1/errors[i]);
        num += data[i]/errors[i];
    }
    float value = num/weight;
    float error = 1/weight;

    std::cout << "The weighted average is: " << value << " +/- " << error << std::endl;
    return;
}