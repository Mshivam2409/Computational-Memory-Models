#include <memory_models.hpp>
using namespace std;
int main()
{
    MultiTraceTheory::Minerva::Minerva m(0.7, 0.4, 0.1, 10);
    vector<double> v(10, 1);
    vector<double> v1(10, -1);
    m.Encode(v);
    m.Encode(v1);
    m.ViewMemory();
    cout << (m.Recognize(v) == true ? "true" : "false");
    DualStoreTheory::SAM::Sam<100> SAM;
    SAM._STS.buffer.push_back(100);
    cout << SAM._STS.buffer;
}