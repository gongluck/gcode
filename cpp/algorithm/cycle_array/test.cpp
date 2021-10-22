/*
 * @Author: gongluck
 * @Date: 2021-10-22 14:20:06
 * @Last Modified by: gongluck
 * @Last Modified time: 2021-10-22 14:50:09
 */

#include <iostream>
#include "cycle_array.hpp"

class A
{
public:
    A()
    {
        std::cout << __FUNCTION__ << std::endl;
    }
    A(const A&)
    {
        std::cout << __FUNCTION__ << std::endl;
    }
    A(A&&)
    {
        std::cout << __FUNCTION__ << std::endl;
    }
    A& operator=(const A&)
    {
        std::cout << __FUNCTION__ << std::endl;
        return *this;
    }
    ~A()
    {
        std::cout << __FUNCTION__ << std::endl;
    }
};

int main()
{
    galgorithm::cycle_array<int, 20> cycle;
    for (int i = 0; i < cycle.size(); ++i)
    {
        cycle.push(i);
    }
    for (auto it = cycle.begin(); it != cycle.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < cycle.size() / 2; ++i)
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

    for (int i = 0; i < cycle.size() /2 ; ++i)
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

    galgorithm::cycle_array<A, 3> cycleA;
    std::cout << "init" << std::endl;
    A a{};
    for (int i = 0; i < cycleA.size(); ++i)
    {
        cycleA.push(a);
        std::cout << "push" << std::endl;
    }

    for (int i = 0; i < cycleA.size(); ++i)
    {
        cycleA.pop(a);
        std::cout << "pop" << std::endl;
    }

    return 0;
}