#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>
#include <functional>
#include <math.h>
#include <cmath>

#ifndef MEMORY_MODELS_MATH_H
#define MEMORY_MODELS_MATH_H
namespace modelmath
{
    // Computes the distance between two std::vectors
    template <typename T1, typename T2>
    double vectors_distance(const std::vector<T1> &a, const std::vector<T2> &b)
    {
        std::vector<double> auxiliary;

        std::transform(a.begin(), a.end(), b.begin(), std::back_inserter(auxiliary), //
                       [](T1 element1, T2 element2) { return std::pow((element1 - element2), 2); });
        auxiliary.shrink_to_fit();

        return sqrt(std::accumulate(auxiliary.begin(), auxiliary.end(), 0.0));
    } // end template vectors_distance

}; // namespace modelmath
#endif
