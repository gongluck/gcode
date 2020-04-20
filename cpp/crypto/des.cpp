/*
 * @Author: gongluck 
 * @Date: 2020-04-20 20:49:31 
 * @Last Modified by: gongluck
 * @Last Modified time: 2020-04-20 20:58:09
 */

#include "des.h"
#include "openssl/des.h"

namespace gcrypto
{

static const int desblocksize = 8;

void desSetParam(const std::string &key, DES_cblock &dkey, DES_key_schedule &schedule)
{
	memcpy(dkey, key.c_str(), desblocksize);
	DES_set_key_unchecked(&dkey, &schedule);
}

std::string DesEcbEncode(const std::string &plain, const std::string &key)
{
	std::string cipher;
	auto originalsize = plain.size();
	if (originalsize == 0 || originalsize % desblocksize != 0 || key.size() != desblocksize)
	{
		return cipher;
	}
	cipher.resize(originalsize);

	DES_cblock dkey;
	DES_key_schedule schedule;
	DES_cblock output;
	desSetParam(key, dkey, schedule);

	for (auto i = 0u; i < plain.size(); i += desblocksize)
	{
		DES_ecb_encrypt((const_DES_cblock *)(plain.c_str() + i), &output, &schedule, DES_ENCRYPT);
		cipher.replace(i, desblocksize, reinterpret_cast<char *>(output), desblocksize);
	}

	return cipher;
}

std::string DesEcbDecode(const std::string &cipher, const std::string &key)
{
	std::string plain;
	auto originalsize = cipher.size();
	if (originalsize == 0 || originalsize % desblocksize != 0 || key.size() != desblocksize)
	{
		return cipher;
	}
	plain.resize(originalsize);

	DES_cblock dkey;
	DES_key_schedule schedule;
	DES_cblock output;
	desSetParam(key, dkey, schedule);

	for (auto i = 0u; i < cipher.size(); i += desblocksize)
	{
		DES_ecb_encrypt((const_DES_cblock *)(cipher.c_str() + i), &output, &schedule, DES_DECRYPT);
		plain.replace(i, desblocksize, reinterpret_cast<char *>(output), desblocksize);
	}

	return plain;
}
} // namespace gcrypto