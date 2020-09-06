/*
 * @Author: gongluck 
 * @Date: 2020-03-23 16:13:01 
 * @Last Modified by: gongluck
 * @Last Modified time: 2020-03-23 16:34:50
 */

#include "convert.h"
#include "../errcode.h"

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

namespace gconvert
{
#ifdef _WIN32
    static int multi2uni(const std::string& multi, std::wstring& uni, UINT code)
    {
        auto len = MultiByteToWideChar(code, 0, multi.c_str(), -1, nullptr, 0);
        if (len <= 0)
        {
            std::cerr << __FILE__ << " : " << __LINE__ << " : " << GetLastError() << std::endl;
            return G_ERROR_INVALIDPARAM;
        }
        WCHAR* buf = new WCHAR[len];
        if (buf == nullptr)
        {
            std::cerr << __FILE__ << " : " << __LINE__ << " : " << "can not new buf, size : " << len << std::endl;
            return G_ERROR_NOBUF;
        }
        len = MultiByteToWideChar(code, 0, multi.c_str(), -1, buf, len);
        uni.assign(buf);
        delete[]buf;
        buf = nullptr;
        return len;
    }

    static int uni2multi(const std::wstring& uni, std::string& multi, UINT code)
    {
        auto len = WideCharToMultiByte(code, 0, uni.c_str(), -1, nullptr, 0, nullptr, nullptr);
        if (len <= 0)
        {
            std::cerr << __FILE__ << " : " << __LINE__ << " : " << GetLastError() << std::endl;
            return G_ERROR_INVALIDPARAM;
        }
        CHAR* buf = new CHAR[len];
        if (buf == nullptr)
        {
            std::cerr << __FILE__ << " : " << __LINE__ << " : " << "can not new buf, size : " << len << std::endl;
            return G_ERROR_NOBUF;
        }
        len = WideCharToMultiByte(code, 0, uni.c_str(), -1, buf, len, nullptr, nullptr);
        multi.assign(buf);
        delete[]buf;
        buf = nullptr;
        return len;
    }
#endif

// ANSI->Unicode
int ansi2uni(const std::string& ansi, std::wstring& uni)
{
#ifdef _WIN32
    return multi2uni(ansi, uni, CP_ACP);
#endif
    return G_ERROR_SUCCEED;
}

// Unicode->ANSI
int uni2ansi(const std::wstring &uni, std::string &ansi)
{
#ifdef _WIN32
    return uni2multi(uni, ansi, CP_ACP);
#endif
    return G_ERROR_SUCCEED;
}

// UTF8->Unicode
int utf82uni(const std::string& utf8, std::wstring& uni)
{
#ifdef _WIN32
    return multi2uni(utf8, uni, CP_UTF8);
#endif
    return G_ERROR_SUCCEED;
}

// Unicode->UTF8
int uni2utf8(const std::wstring& uni, std::string& utf8)
{
#ifdef _WIN32
    return uni2multi(uni, utf8, CP_UTF8);
#endif
    return G_ERROR_SUCCEED;
}

// ANSI->UTF8
int ansi2utf8(const std::string &ansi, std::string &utf8)
{
    std::wstring uni;
    auto len = ansi2uni(ansi, uni);
    if (len <= 0)
    {
        return G_ERROR_INTERNAL;
    }
    return uni2utf8(uni, utf8);
}

// UTF8->ANSI
int utf82ansi(const std::string &utf8, std::string &ansi)
{
    std::wstring uni;
    auto len = utf82uni(utf8, uni);
    if (len <= 0)
    {
        return G_ERROR_INTERNAL;
    }
    return uni2ansi(uni, ansi);
}
} // namespace gconvert