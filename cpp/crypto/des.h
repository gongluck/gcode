/*
 * @Author: gongluck 
 * @Date: 2020-04-20 20:49:21 
 * @Last Modified by: gongluck
 * @Last Modified time: 2020-04-20 20:58:12
 */

#pragma once

#include <string>

namespace gcrypto
{
std::string DesEcbEncode(const std::string &plain, const std::string &key);
std::string DesEcbDecode(const std::string &cipher, const std::string &key);
} // namespace gcrypto
