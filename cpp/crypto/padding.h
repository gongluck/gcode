/*
 * @Author: gongluck 
 * @Date: 2020-04-18 16:28:11 
 * @Last Modified by: gongluck
 * @Last Modified time: 2020-04-18 16:31:13
 */

#pragma once

#include <string>

namespace gcrypto
{
std::string PKCS5Padding(const std::string &in, uint32_t bsize);
std::string UNPKCS5Padding(const std::string &in, uint32_t bsize);
} // namespace gcrypto
