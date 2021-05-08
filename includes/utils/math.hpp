#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>
#include <functional>
#include <math.h>
#include <cmath>

namespace modelmath
{
    // Computes the distance between two std::vectors
    template <typename T>
    double vectors_distance(const std::vector<T> &a, const std::vector<T> &b)
    {
        std::vector<double> auxiliary;

        std::transform(a.begin(), a.end(), b.begin(), std::back_inserter(auxiliary), //
                       [](T element1, T element2) { return std::pow((element1 - element2), 2); });
        auxiliary.shrink_to_fit();

        return sqrt(std::accumulate(auxiliary.begin(), auxiliary.end(), 0.0));
    } // end template vectors_distance

} // namespace modelmath
;
