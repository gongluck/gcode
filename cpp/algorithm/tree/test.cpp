/*
 * @Author: gongluck 
 * @Date: 2020-09-06 16:46:21 
 * @Last Modified by: gongluck
 * @Last Modified time: 2020-09-06 16:59:35
 */

#include <iostream>
#include "tree.h"

void print(int *data)
{
    std::cout << *data << "\t";
}

int main()
{
    int data[] = {24, 25, 13, 35, 23, 26, 67, 47, 38, 98, 20, 13, 17, 49, 12, 21, 9, 18, 14, 15};
    int length = sizeof(data) / sizeof(int);

    galgorithm::BTree<int> tree = {nullptr};
    for (int i = 0; i < length; ++i)
    {
        galgorithm::Insert<int>(&tree, data[i]);
    }

    galgorithm::Traversal<int>(tree.root, print);
    std::cout << std::endl;

    return 0;
}