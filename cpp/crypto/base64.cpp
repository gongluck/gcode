#include "base64.h"

#include <map>

static const unsigned eblocksize = 3;
static const unsigned dblocksize = 4;
static const unsigned invalidindex = 0xfe;
static const unsigned endindex = 0xff;
static const char Base64Table[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="};

class UnBase64Table
{
public:
	UnBase64Table()
	{
		for (unsigned i = 0; i < sizeof(Base64Table) - 2; ++i)
		{
			unbase64table_[Base64Table[i]] = i;
		}
		unbase64table_[Base64Table[sizeof(Base64Table) - 2]] = invalidindex;
	}

	unsigned operator[](char c) const
	{
		return unbase64table_.at(c);
	}

private:
	std::map<char, unsigned> unbase64table_;
};
static UnBase64Table g_UnBase64Table;

namespace gcrypto
{
std::string Base64Encode(const std::string &plain)
{
	std::string cipher;
	size_t index = 0;
	auto originalsize = plain.size();
	if (originalsize == 0)
	{
		return cipher;
	}
	auto intc = originalsize / eblocksize;
	auto left = originalsize % eblocksize;
	cipher.resize(intc * dblocksize + (left != 0 ? dblocksize : 0));
	unsigned c1 = endindex, c2 = endindex, c3 = endindex, c4 = endindex;
	for (auto i = 0u; i < originalsize; i += eblocksize)
	{
		/* 0b12345678 0b12345678 0b12345678 */
		/*     123456     781234     567812     345678 */
		/* 0b00123456 0b00781234 0b00567812 0b00345678 */
		if (i + eblocksize <= originalsize)
		{
			c1 = (plain[i] >> 2) & 0b00111111;
			c2 = ((plain[i + 1] >> 4) & 0b00001111) + ((plain[i] << 4) & 0b00110000);
			c3 = ((plain[i + 2] >> 6) & 0b00000011) + ((plain[i + 1] << 2) & 0b00111100);
			c4 = (plain[i + 2] & 0b00111111);
		}
		else if (left != 0)
		{
			intc *= eblocksize;
			c1 = (plain[intc] >> 2) & 0b00111111;
			c2 = ((plain[intc] << 4) & 0b00110000) + (left > 1 ? ((plain[intc + 1] >> 4) & 0b00001111) : 0);
			c3 = (left > 1) ? ((plain[intc + 1] << 2) & 0b00111100) : 64;
			c4 = 64;
		}

		cipher[index++] = Base64Table[c1];
		cipher[index++] = Base64Table[c2];
		cipher[index++] = Base64Table[c3];
		cipher[index++] = Base64Table[c4];
	}

	return cipher;
}

std::string Base64Decode(const std::string &cipher)
{
	std::string plain;
	size_t index = 0;
	auto originalsize = cipher.size();
	if (originalsize % dblocksize != 0 || originalsize == 0)
	{
		return plain;
	}
	auto truesize = originalsize / dblocksize * eblocksize;
	plain.resize(truesize);
	unsigned c1, c2, c3, c4;
	for (auto i = 0u; i < originalsize; i += dblocksize)
	{
		/* 0b00123456 0b00123456 0b00123456 0b00123456 */
		/*     12345612     34561234     56123456      */
		/* 0b12345612 0b34561234 0b56123456	           */
		c1 = g_UnBase64Table[cipher[i]];
		c2 = g_UnBase64Table[cipher[i + 1]];
		c3 = g_UnBase64Table[cipher[i + 2]];
		c4 = g_UnBase64Table[cipher[i + 3]];

		plain[index++] = ((c1 << 2) & 0b11111100) + ((c2 >> 4) & 0b00000011);
		plain[index++] = ((c2 << 4) & 0b11110000) + ((c3 >> 2) & 0b00001111);
		plain[index++] = ((c3 << 6) & 0b11000000) + (c4 & 0b00111111);
	}

	if (c3 == invalidindex)
	{
		plain[index - eblocksize + 1] = (c2 << 4) & 0b11110000;
		truesize -= 2;
	}
	else if (c4 == invalidindex)
	{
		plain[index - eblocksize + 2] = (c3 << 6) & 0b11000000;
		truesize -= 1;
	}
	plain.resize(truesize);

	return plain;
}
} // namespace gcrypto