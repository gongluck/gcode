/*
 * @Author: gongluck
 * @Date: 2021-10-22 14:20:06
 * @Last Modified by: gongluck
 * @Last Modified time: 2021-10-22 17:21:38
 */

#include <iostream>
#include "cycle_array.hpp"

class A
{
public:
    A()
    {
        std::cout << __FUNCTION__ << __LINE__ << std::endl;
    }
    A(const A&)
    {
        std::cout << __FUNCTION__ << __LINE__ << std::endl;
    }
    A(A&&)
    {
        std::cout << __FUNCTION__ << __LINE__ << std::endl;
    }
    A& operator=(const A&)
    {
        std::cout << __FUNCTION__ << __LINE__ << std::endl;
        return *this;
    }
    A& operator=(A&&)
    {
        std::cout << __FUNCTION__ << __LINE__ << std::endl;
        return *this;
    }
    ~A()
    {
        std::cout << __FUNCTION__ << __LINE__ << std::endl;
    }
};

galgorithm::cycle_array<int, 20> cycle;
galgorithm::cycle_array<A, 10> cycleA;
A a{};
A b[10];

int main()
{
    std::cout << "begin" << std::endl;
    for (int i = 0; i < cycle.capticty(); ++i)
    {
        cycle.push(i);
    }
    for (auto it = cycle.begin(); it != cycle.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < cycle.capticty() / 2; ++i)
    {
        int tmp;
        cycle.pop(tmp);
        std::cout << "pop " << tmp << std::endl;
    }
    for (auto it = cycle.begin(); it != cycle.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < cycle.capticty() /2 ; ++i)
    {
        cycle.push(i + 100);
    }
    for (auto it = cycle.begin(); it != cycle.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    int array[10] = {};
    cycle.pop(array, 5);
    for (auto it = cycle.begin(); it != cycle.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    cycle.push(array, 5);
    for (auto it = cycle.begin(); it != cycle.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    cycleA.push(A{});
    std::cout << "push" << std::endl;

    cycleA.pop(a);
    std::cout << "pop" << std::endl;

    std::cout << "*********************" << std::endl;
    
    cycleA.push(b, 10);
    std::cout << "push" << std::endl;
    cycleA.pop(b, 10);
    std::cout << "pop" << std::endl;

    std::cout << "end" << std::endl;
    return 0;
}