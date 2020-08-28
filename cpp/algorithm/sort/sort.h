/*
 * @Author: gongluck 
 * @Date: 2020-08-23 14:49:53 
 * @Last Modified by:   gongluck 
 * @Last Modified time: 2020-08-23 14:49:53 
 */
#pragma once

#include <string>

namespace galgorithm
{
    //插入排序
    template <typename T>
    void insert_sort(T *data, int length, int gap)
    {
        T tmp = 0;
        int i = 0, j = 0;

        for (i = gap; i < length; ++i)
        {
            // 待插入值
            tmp = data[i];
            for (j = i - gap; j >= 0 && (data[j] > tmp) /*如果前面的值比待插入值大*/; j -= gap)
            {
                // 将前面的值（data[j]）后移
                data[j + gap] = data[j];
            }
            data[j + gap] = tmp;
        }
    }
    //希尔排序
    template <typename T>
    void shell_sort(T *data, int length)
    {
        int gap = 0;

        // 计算步长，进行插入排序
        for (gap = length / 2; gap > 0; gap /= 2)
        {
            insert_sort(data, length, gap);
        }
    }
    //归并排序
    template <typename T>
    void merge_sort(T *data, int start, int end)
    {
        //排序[start,end)
        if (start < end - 1)
        {
            int middle = start + (end - start) / 2;
            merge_sort(data, start, middle); //排序[start,middle)
            merge_sort(data, middle, end);   //排序[middle,end)

            T *tmp = (T *)malloc(sizeof(T) * (end - start)); //临时数组
            //合并[start, middle)和[middle, end)
            int i = start, j = middle, k = 0;
            while (i < middle && j < end)
            {
                tmp[k++] = data[i] < data[j] ? data[i++] : data[j++];
            }
            while (i < middle)
            {
                tmp[k++] = data[i++];
            }
            //处理剩余数据
            while (j < end)
            {
                tmp[k++] = data[j++];
            }
            for (int i = 0; i < end - start; ++i)
            {
                data[start + i] = tmp[i];
            }
            free(tmp);
            tmp = nullptr;
        }
    }
    //快速排序
    template <typename T>
    void quick_sort(T *data, int start, int end)
    {
        if (start < end - 1)
        {
            T key = data[start];
            int i = start, j = end - 1;
            while (i < j)
            {
                while (i < j && data[j] >= key)
                {
                    --j;
                }
                data[i] = data[j];
                while (i < j && data[i] <= key)
                {
                    ++i;
                }
                data[j] = data[i];
            }
            data[i] = key; //data[i]确定为key

            quick_sort(data, start, i);
            quick_sort(data, i + 1, end);
        }
    }
} // namespace galgorithm