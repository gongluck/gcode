/*
 * @Author: gongluck 
 * @Date: 2020-04-18 16:28:50 
 * @Last Modified by: gongluck
 * @Last Modified time: 2020-04-18 16:31:12
 */

#include "padding.h"

namespace gcrypto
{
std::string PKCS5Padding(const std::string &in, uint32_t bsize)
{
	std::string result;
	auto size = in.size();
	decltype(size) padding = bsize - size % bsize;
	result.assign(in);
	result.resize(size + padding, padding);
	return result;
}

std::string UNPKCS5Padding(const std::string &in, uint32_t bsize)
{
	std::string result;
	auto size = in.size();
	decltype(size) padding = in[size - 1];
	result.assign(in.c_str(), size - padding);
	return result;
}
} // namespace gcrypto
