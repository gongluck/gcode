/*
 * @Author: gongluck 
 * @Date: 2020-04-05 21:40:35 
 * @Last Modified by: gongluck
 * @Last Modified time: 2020-04-05 21:43:38
 */

#include "process.h"

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <TlHelp32.h>
#include <tchar.h>
#include <atlconv.h>
#endif

namespace gprocess
{
void* gethandle(const char* processname)
{
    if (processname == nullptr)
    {
        return nullptr;
    }

#ifdef _WIN32
    auto hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        std::cerr << __FILE__ << " : " << __LINE__ << " : " << GetLastError() << std::endl;
        return nullptr;
    }
    PROCESSENTRY32 pe = { sizeof(pe) };
    USES_CONVERSION; 
    auto processT = A2T(processname);

    auto fOk = FALSE;
    for (fOk = Process32First(hSnapshot, &pe); fOk; fOk = Process32Next(hSnapshot, &pe))
    {
        if (!_tcscmp(pe.szExeFile, processT))
        {
            CloseHandle(hSnapshot);
            return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe.th32ProcessID);
        }
    }
    CloseHandle(hSnapshot);
    return nullptr;
#endif

    return 0;
}
} // namespace gprocess