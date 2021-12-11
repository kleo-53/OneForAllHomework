#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MODULE 999999000001
#define BASE_NUMBER 2

long long hash(const char* line, const int start, const int end, const long long module, const int base)
{
	int hash = 0;
	for (int i = start; i < end; i++) {
		hash = (hash * base + line[i] - 31) % module;
	}
	if (hash < 0)
	{
		hash += module;
	}
	return hash;
}

long long binPower(long long number, int power, const long long module)
{
	int res = 1;
	while (power)
		if (power & 1) {
			res = (res * number) % module;
			--power;
		}
		else {
			number *= number;
			power >>= 1;
		}
	return res;
}

int rollingHash(const long long previousHash, char* line, const int newSymbol, const long long module, 
	const int previousPower, const int base, const int patternSize)
{
	return ((previousHash - (line[newSymbol - 1] - 31) * previousPower) * base + line[newSymbol + patternSize - 1] - 31) % module;
}

bool isSimple(const char* textLine, const int start, const int end, char* pattern)
{
	for (int i = start; i < end; ++i)
	{
		if (textLine[i] != pattern[i - start])
		{
			return false;
		}
	}
	return true;
}

int RabinKarp(const char* textLine, const char* pattern)
{
	const int textSize = strlen(textLine);
	const int patternSize = strlen(pattern);
    const long long hsub = hash(pattern, 0, patternSize, MODULE, BASE_NUMBER);
	long long hs = hash(textLine, 0, patternSize, MODULE, BASE_NUMBER);
	const long long previousPower = binPower(BASE_NUMBER, patternSize - 1, MODULE);
	int flag = 0;
	for (int i = 1; i < (textSize - patternSize + 2); ++i)
	{
		if (hs == hsub) 
		{
			if (isSimple(textLine, i - 1, i + patternSize - 1, pattern))
			{
				return i;
			}
		}
		hs = rollingHash(hs, textLine, i, MODULE, previousPower, BASE_NUMBER, patternSize);
		if (hs < 0) {
			hs += MODULE;
		}
	}
	return -1;
}
