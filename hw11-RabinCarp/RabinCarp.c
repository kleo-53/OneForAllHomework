#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MODULE 999999000001
#define BASE_NUMBER 2

long long hash(const char* line, const int start, const int end, const long long module, const int base)
{
    long long hash = 0;
    for (int i = start; i < end; i++) 
    {
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
    long long res = 1;
    while (power)
    {
        if (power & 1) {
            res = (res * number) % module;
            --power;
        }
        else {
            number *= number;
            power >>= 1;
        }
    }
    return res;
}

long long rollingHash(const long long previousHash, const char* line, const int newSymbol, const long long module, 
    const long long previousPower, const int base, const int patternSize)
{
    return ((previousHash - (line[newSymbol - 1] - 31) * previousPower) * base + line[newSymbol + patternSize - 1] - 31) % module;
}

bool isEqual(const char* textLine, const int start, const int end, const char* pattern)
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

int rabinKarp(const char* textLine, const char* pattern)
{
    const int textSize = (int)strlen(textLine);
    const int patternSize = (int)strlen(pattern);
    const long long patternHash = hash(pattern, 0, patternSize, MODULE, BASE_NUMBER);
    long long currentHash = hash(textLine, 0, patternSize, MODULE, BASE_NUMBER);
    const long long previousPower = binPower(BASE_NUMBER, patternSize - 1, MODULE);
    for (int i = 1; i < (textSize - patternSize + 2); ++i)
    {
        if (currentHash == patternHash)
        {
            if (isEqual(textLine, i - 1, i + patternSize - 1, pattern))
            {
                return i;
            }
        }
        currentHash = rollingHash(currentHash, textLine, i, MODULE, previousPower, BASE_NUMBER, patternSize);
        if (currentHash < 0) {
            currentHash += MODULE;
        }
    }
    return -1;
}
