#include <iostream>
#include "datanalysis.h"

int main()
{
    int n_points = -666;
    std::cout << "How many data points do you have? ";
    std::cin >> n_points;
    std::cout << "Please input data in this format: value error." << std::endl;
    
    float value_array[n_points];
    float error_array[n_points];
    
    bool input_state = true;
    float value = -666;
    float error = -666;
    for (int i = 0; i < n_points; i++)
    {
        std::cin >> value >> error;
        if ((char) value == 'q' || (char) error == 'q')
            break;
        value_array[i] = value;
        error_array[i] = error;
    }

    std::tuple<float, float> result = wavg(value_array, error_array, n_points);
    std::cout << "The weighted average is: " << std::get<0>(result) << " +/- " << std::get<1>(result) << std::endl;
}