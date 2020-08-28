/*
 * @Author: gongluck 
 * @Date: 2020-08-23 14:48:42 
 * @Last Modified by:   gongluck 
 * @Last Modified time: 2020-08-23 14:48:42 
 */
#include "sort.h"

#include <iostream>
#include <ctime>

void printdata(int *data, int length)
{
    for (int i = 0; i < length; ++i)
    {
        std::cout << data[i] << "\t";
    }
    std::cout << std::endl;
}

int main()
{
    int data[] = {23, 64, 24, 12, 9, 16, 53, 57, 71, 79, 87, 97};
    int length = sizeof(data) / sizeof(int);
    printdata(data, length);

    auto begin = time(nullptr);

    //galgorithm::insert_sort(data, length, 1);
    //galgorithm::shell_sort(data, length);
    //galgorithm::merge_sort(data, 0, length);
    galgorithm::quick_sort(data, 0, length);

    printdata(data, length);
    std::cout << "use time : " << difftime(time(nullptr), begin) << " ms" << std::endl;

    return 0;
}
