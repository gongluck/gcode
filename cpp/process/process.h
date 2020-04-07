/*
 * @Author: gongluck
 * @Date: 2020-04-05 21:30:45
 * @Last Modified by: gongluck
 * @Last Modified time: 2020-04-05 21:40:20
 */

#pragma once

#include <vector>
#include <memory>

namespace gprocess
{
    typedef struct __PROCESSINFO
    {
        uint64_t processid = 0;
        uint64_t parentid = 0;
    }ProcessInfo;
    typedef struct __WINDOWINFO
    {
        uint64_t processid = 0;
        std::vector<void*> windows;
        std::vector<std::shared_ptr<__WINDOWINFO>> childs;
    }WindowInfo;

    int gethandle(const char* processname, std::vector<ProcessInfo>&result);

    int getallwindows(WindowInfo* info);
} // namespace gprocess