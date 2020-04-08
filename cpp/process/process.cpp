/*
 * @Author: gongluck
 * @Date: 2020-04-05 21:40:35
 * @Last Modified by: gongluck
 * @Last Modified time: 2020-04-05 21:43:38
 */

#include "process.h"
#include "../errcode.h"

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <TlHelp32.h>
#include <tchar.h>
#include <atlconv.h>
#endif

namespace gprocess
{
    int gethandle(const char* processname, std::vector<ProcessInfo>& result)
    {
        if (processname == nullptr)
        {
            return G_ERROR_INVALIDPARAM;
        }

#ifdef _WIN32
        auto hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        USES_CONVERSION;
        auto processT = A2T(processname);
        if (hSnapshot == INVALID_HANDLE_VALUE || processT == nullptr)
        {
            std::cerr << __FILE__ << " : " << __LINE__ << " : " << GetLastError() << std::endl;
            return G_ERROR_INTERNAL;
        }

        result.clear();
        ProcessInfo info = { 0 };
        PROCESSENTRY32 pe = { sizeof(pe) };
        auto fOk = FALSE;
        for (fOk = Process32First(hSnapshot, &pe); fOk; fOk = Process32Next(hSnapshot, &pe))
        {
            if (!_tcscmp(pe.szExeFile, processT))
            {
                info.processid = pe.th32ProcessID;
                info.parentid = pe.th32ParentProcessID;
                result.push_back(info);
            }
        }
        CloseHandle(hSnapshot);
        return G_ERROR_SUCCEED;
#endif

        return G_ERROR_SUCCEED;
    }

#ifdef _WIN32
    BOOL CALLBACK EnumChildWindowCB(HWND h, LPARAM l)
    {
        auto pinfo = reinterpret_cast<WindowInfo*>(l);
        DWORD pid = 0;
        GetWindowThreadProcessId(h, &pid);
        if (pid == pinfo->processid)
        {
            auto pchild = std::make_shared<WindowInfo>();
            pchild->processid = pid;
            pchild->window = h;
            pinfo->childs.push_back(pchild);
            EnumChildWindows(h, EnumChildWindowCB, reinterpret_cast<LPARAM>(pchild.get()));
        }
        return TRUE;
    }
    BOOL CALLBACK EnumWindowCB(HWND h, LPARAM l)
    {
        auto pinfo = reinterpret_cast<WindowInfo*>(l);
        DWORD pid = 0;
        GetWindowThreadProcessId(h, &pid);
        if (pid == pinfo->processid)
        {
            auto pchild = std::make_shared<WindowInfo>();
            pchild->processid = pid;
            pchild->window = h;
            pinfo->childs.push_back(pchild);
            EnumChildWindows(h, EnumChildWindowCB, reinterpret_cast<LPARAM>(pchild.get()));
        }
        return TRUE;
    }
#endif

    int getallwindows(WindowInfo* info)
    {
#ifdef _WIN32
        if (EnumWindows(EnumWindowCB, reinterpret_cast<LPARAM>(info)) != TRUE)
        {
            std::cerr << __FILE__ << " : " << __LINE__ << " : " << GetLastError() << std::endl;
            return G_ERROR_INTERNAL;
        }
        return G_ERROR_SUCCEED;
#endif
        return G_ERROR_SUCCEED;
    }
} // namespace gprocess