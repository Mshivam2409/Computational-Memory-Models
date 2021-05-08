#include <memory_models.hpp>
using namespace std;
int main()
{
    MultiTraceTheory::Minerva m(0.7);
    vector<int> v(10, 1);
    vector<int> v1(10, -1);
    m.Encode(v);
    m.Encode(v1);
    m.ViewMemory();
    m.CalculateSimilarity(vector<int>(10, 0));
}