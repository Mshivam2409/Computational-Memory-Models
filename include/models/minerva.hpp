#include <models/main.hpp>
#ifndef MEMORY_MODEL_MINERVA_H
#define MEMORY_MODEL_MINERVA_H
namespace MultiTraceTheory
{

    namespace Minerva
    {

        class Minerva : public Memory::MemoryModel
        {
        private:
            const double _LEARNING_RATE;
            const double _DECAY_RATE;
            const double _THRESHOLD;
            const unsigned int _ATTRIBUTE_SIZE;
            std::vector<double> CalculateSimilarity(const std::vector<double> &);

        public:
            Minerva(double _LEARNING_RATE, double _DECAY_RATE, double _THRESHOLD, unsigned int _ATTRIBUTE_SIZE);
            ~Minerva();
            void Encode(std::vector<double>);
            bool Recognize(std::vector<double> &);
        };

        Minerva ::Minerva(double _LEARNING_RATE, double _DECAY_RATE, double _THRESHOLD, unsigned int _ATTRIBUTE_SIZE) : _LEARNING_RATE(_LEARNING_RATE), _DECAY_RATE(_DECAY_RATE), _THRESHOLD(_THRESHOLD), _ATTRIBUTE_SIZE(_ATTRIBUTE_SIZE){};

        Minerva ::~Minerva(){};

        void Minerva ::Encode(std::vector<double> new_memory)
        {
            std::vector<int> lost_memory;
            std::vector<int> memory_range(new_memory.size());
            std::cout << (new_memory.size() - (int)(_LEARNING_RATE * new_memory.size()));
            std::iota(std::begin(memory_range), std::end(memory_range), 0);
            std::sample(memory_range.begin(), memory_range.end(), std::back_inserter(lost_memory),
                        (new_memory.size() - (int)(_LEARNING_RATE * new_memory.size())), std::mt19937{std::random_device{}()});
            std::cout << lost_memory;
            for (size_t i = 0; i < lost_memory.size(); i++)
                new_memory[lost_memory[i]] = 0;

            this->memory.push_back(new_memory);
        }

        std::vector<double> Minerva::CalculateSimilarity(const std::vector<double> &probe)
        {
            if (memory.size() == 0)
                throw Memory::Exception("Empty Memory");
            std::vector<double> similarity_matrix(memory.size());
            std::transform(std::execution::par_unseq, memory.cbegin(), memory.cend(), similarity_matrix.begin(),
                           [probe](std::vector<double> c) -> double { return exp(-1 * modelmath::vectors_distance(c, probe)); });
            std::cout << similarity_matrix;
            return similarity_matrix;
        }

        bool Minerva::Recognize(std::vector<double> &cue)
        {
            auto ss = this->CalculateSimilarity(cue);
            double summed = std::accumulate(ss.begin(), ss.end(), 0.0);
            return summed > this->_THRESHOLD ? true : false;
        }

    } // namespace Minerva

} // namespace MultiTraceTheory
#endif