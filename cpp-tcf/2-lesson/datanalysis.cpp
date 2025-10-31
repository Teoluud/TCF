#include "datanalysis.h"
#include <iostream>
#include <cmath>
//#include <tuple>

std::tuple<float, float> wavg(const float data[], const float errors[], int length)
{
    double sum_weight = 0.0;
    double sum_num = 0.0;
    double weight = -666.0;
    for (int i = 0; i < length; i++)
    {
        weight = 1.0 / (errors[i] * errors[i]);
        sum_num += data[i] * weight;
        sum_weight += weight;
    }
    float value = sum_num/sum_weight;
    float error = std::sqrt(1.0 / sum_weight);
    return std::make_tuple(value, error);
}