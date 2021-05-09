#include <models/main.hpp>
#ifndef MEMORY_MODEL_SAM_H
#define MEMORY_MODEL_SAM_H
namespace DualStoreTheory
{

    template <typename T, std::size_t N>
    struct STS
    {
        const unsigned int BUFFER_SIZE = N;
        std::circular_buffer<T, N> buffer;
        STS() : buffer(std::circular_buffer<double, N>()){};
    };

    namespace SAM
    {

        template <std::size_t STS_BUF_SIZE>
        class Sam
        {

        public:
            Sam();
            ~Sam();
            STS<double, STS_BUF_SIZE> _STS;
        };

        template <std::size_t N>
        Sam<N>::Sam(/* args */) : _STS(STS<double, N>()){};

        template <std::size_t N>
        Sam<N>::~Sam()
        {
        }

    } // namespace SAM

} // namespace DualStoreTheory
#endif