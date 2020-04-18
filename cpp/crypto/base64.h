/*
 * @Author: gongluck 
 * @Date: 2020-04-18 16:28:42 
 * @Last Modified by: gongluck
 * @Last Modified time: 2020-04-18 16:31:11
 */

#pragma once

#include <string>

namespace gcrypto
{
std::string Base64Encode(const std::string &plain);
std::string Base64Decode(const std::string &cipher);
} // namespace gcrypto
