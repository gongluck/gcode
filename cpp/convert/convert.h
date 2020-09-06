/*
 * @Author: gongluck 
 * @Date: 2020-03-23 16:06:23 
 * @Last Modified by: gongluck
 * @Last Modified time: 2020-03-23 16:09:30
 */

// Character encoding conversion

#pragma once

#include <string>

namespace gconvert
{
// ANSI->Unicode
int ansi2uni(const std::string& ansi, std::wstring& uni);

// Unicode->ANSI
int uni2ansi(const std::wstring& uni, std::string& ansi);

// UTF8->Unicode
int utf82uni(const std::string& utf8, std::wstring& uni);

// Unicode->UTF8
int uni2utf8(const std::wstring& uni, std::string& utf8);

// ANSI->UTF8
int ansi2utf8(const std::string& ansi, std::string& utf8);

// UTF8->ANSI
int utf82ansi(const std::string& utf8, std::string& ansi);
} // namespace gconvert