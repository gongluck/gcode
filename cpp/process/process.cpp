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

#define CHECKEQANDRETURN(ret, comp, err)\
if (ret == comp)\
{\
    std::cerr << __FILE__ << " : " << __LINE__ << " : " << GetLastError() << std::endl;\
    return err;\
}

namespace gprocess
{
    int gethandle(const char* processname, std::vector<ProcessInfo>& result)
    {
        CHECKEQANDRETURN(processname, nullptr, G_ERROR_INVALIDPARAM);

#ifdef _WIN32
        auto hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        CHECKEQANDRETURN(hSnapshot, INVALID_HANDLE_VALUE, G_ERROR_INTERNAL);
        USES_CONVERSION;
        auto processT = A2T(processname);
        CHECKEQANDRETURN(processT, nullptr, G_ERROR_INTERNAL);

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
        auto ret = EnumWindows(EnumWindowCB, reinterpret_cast<LPARAM>(info));
        CHECKEQANDRETURN(ret, FALSE, G_ERROR_INTERNAL);
        return G_ERROR_SUCCEED;
#endif
        return G_ERROR_SUCCEED;
    }

    int injectdll(const std::wstring& dllname, uint64_t processid, uint64_t* hthread)
    {
#ifdef _WIN32
        auto hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processid);
        CHECKEQANDRETURN(hprocess, nullptr, G_ERROR_INTERNAL);
        auto buf = VirtualAllocEx(hprocess, nullptr, dllname.size(), MEM_COMMIT, PAGE_READWRITE);
        CHECKEQANDRETURN(buf, nullptr, G_ERROR_INTERNAL);
        auto ret = WriteProcessMemory(hprocess, buf, reinterpret_cast<LPVOID>(const_cast<wchar_t*>(dllname.c_str())), dllname.size(), nullptr);
        CHECKEQANDRETURN(ret, FALSE, G_ERROR_INTERNAL);
        static auto hmod = GetModuleHandleW(L"kernel32.dll");
        CHECKEQANDRETURN(hmod, nullptr, G_ERROR_INTERNAL);
        static auto pfunc = GetProcAddress(hmod, "LoadLibraryW");
        CHECKEQANDRETURN(pfunc, nullptr, G_ERROR_INTERNAL);
        *hthread = reinterpret_cast<uint64_t>(CreateRemoteThread(hprocess, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(pfunc), buf, 0, nullptr));
#endif
        return G_ERROR_SUCCEED;
    }
} // namespace gprocess