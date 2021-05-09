#include <bits/stdc++.h>
#include <utils/include.hpp>
#include <execution>
#include <experimental/numeric>
#ifndef MEMORY_MODELS_H
#define MEMORY_MODELS_H
namespace Memory
{
    class MemoryModel
    {
    protected:
        std::vector<std::vector<double>> memory;

    public:
        MemoryModel(/* args */);
        virtual ~MemoryModel();
        void Encode(std::vector<double>);
        bool Recognize(std::vector<double>);
        void ViewMemory();
    };

    MemoryModel::MemoryModel(/* args */)
    {
    }

    MemoryModel::~MemoryModel()
    {
    }

    void MemoryModel ::ViewMemory()
    {
        std::cout << memory << "\n"
                  << "Memory Allocated: "
                  << (memory.size() > 0 ? sizeof(double) * memory.size() * memory[0].size() : 0)
                  << " Bytes";
    }

    class Exception : public std::exception
    {
    public:
        /** Constructor (C strings).
     *  @param message C-style string error message.
     *                 The string contents are copied upon construction.
     *                 Hence, responsibility for deleting the char* lies
     *                 with the caller. 
     */
        explicit Exception(const char *message)
            : msg_(message) {}

        /** Constructor (C++ STL strings).
     *  @param message The error message.
     */
        explicit Exception(const std::string &message)
            : msg_(message) {}

        /** Destructor.
     * Virtual to allow for subclassing.
     */
        virtual ~Exception() noexcept {}

        /** Returns a pointer to the (constant) error description.
     *  @return A pointer to a const char*. The underlying memory
     *          is in posession of the Exception object. Callers must
     *          not attempt to free the memory.
     */
        virtual const char *what() const noexcept
        {
            return msg_.c_str();
        }

    protected:
        /** Error message.
     */
        std::string msg_;
    };

} // namespace MemoryModel
#endif
