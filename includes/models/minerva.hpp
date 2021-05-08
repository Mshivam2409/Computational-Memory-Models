#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <utils/prettyprint.hpp>
#include <utils/parallel-util.hpp>
#include <utils/math.hpp>
#include <execution>
#include <experimental/numeric>

namespace MultiTraceTheory
{

    class Minerva
    {
    private:
        std::vector<std::vector<int>> memory;
        double learning_rate;
        double decay_rate;

    public:
        Minerva(double learning_rate);
        ~Minerva();
        void Encode(std::vector<int>);
        void ViewMemory();
        std::vector<double> CalculateSimilarity(std::vector<int>);
        bool Recognize(std::vector<int>, double);
    };

    Minerva ::Minerva(double learning_rate)
    {
        this->learning_rate = learning_rate;
    }

    Minerva ::~Minerva()
    {
    }

    void Minerva ::Encode(std::vector<int> new_memory)
    {
        std::vector<int> lost_memory;
        std::vector<int> memory_range(new_memory.size());
        std::cout << (new_memory.size() - (int)(learning_rate * new_memory.size()));
        std::iota(std::begin(memory_range), std::end(memory_range), 0);
        std::sample(memory_range.begin(), memory_range.end(), std::back_inserter(lost_memory),
                    (new_memory.size() - (int)(learning_rate * new_memory.size())), std::mt19937{std::random_device{}()});
        std::cout << lost_memory;
        for (size_t i = 0; i < lost_memory.size(); i++)
        {
            new_memory[lost_memory[i]] = 0;
        }

        this->memory.push_back(new_memory);
    }

    void Minerva ::ViewMemory()
    {
        std::cout << memory << "\n"
                  << "Memory Allocated: " << sizeof(int) * memory.size() * 10 << " Bytes";
    }

    std::vector<double> Minerva::CalculateSimilarity(std::vector<int> probe)
    {
        std::vector<double> similarity_matrix(memory.size());
        std::transform(std::execution::par_unseq, memory.cbegin(), memory.cend(), similarity_matrix.begin(),
                       [probe](std::vector<int> c) -> double { return exp(-1 * modelmath::vectors_distance(c, probe)); });
        std::cout << similarity_matrix;
        return similarity_matrix;
    }

    bool Minerva::Recognize(std::vector<int> cue, double threshold)
    {
        auto ss = this->CalculateSimilarity(cue);
        double summed = std::accumulate(ss.begin(), ss.end(), 0.0);
        return summed > threshold ? true : false;
    }

} // namespace MultiTraceTheory
