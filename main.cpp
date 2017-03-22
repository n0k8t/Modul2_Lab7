#include "TVector.h"

template<typename T>
void printVector(const TVector<T> &vec)
{
    for (int i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
}

int main()
{
    TVector <int>vec;
    for (int i = 0; i < 32; ++i)
        vec.push_back(i);

    printVector(vec); // 1

    vec.insert(vec.begin() + 10, 1000);
    printVector(vec); // 2

    vec.erase(vec.begin(), vec.begin() + 10);          // 0 1 2 3 4 5 6 7 8 9 10
    printVector(vec); // 3

    vec.erase(vec.begin());
    printVector(vec); // 4

    std::cout << vec.front() << std::endl;// 5
    std::cout << vec.back() << std::endl; // 6

    vec.pop_back();
    std::cout << vec.back() << std::endl; // 7

    size_t oldSize = vec.size();
    vec.resize(44);
    printVector(vec); // 8

    vec.resize(oldSize);
    printVector(vec); // 9

    TVector <int>vec2;
    for (int i = 0; i < 2; ++i)
        vec2.push_back(i);

    vec2.swap(vec);
    printVector(vec2); //10
    printVector(vec); //11

    vec2 = vec;
    printVector(vec2);   //12
    printVector(vec);    //13

    try
    {
        TVector<int>::value_type item = vec2.at(1000000);
    }
    catch (const std::exception & e)
    {
        std::cout << e.what();
    }

    try
    {
        vec2.resize(UINT64_MAX);
    }
    catch (const std::exception & e)
    {
        std::cout << e.what();
    }
}