#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 32

void BinToDecimalString(char* string, char* result)
{
	const int size = (int)strlen(string);
	int digit = 1;
	int decimalResult = 0;
	for (int i = size - 1; i >= 0; --i)
	{
		if (string[i] == '1')
		{
			decimalResult += digit;
		}
		digit *= 2;
	}
	_itoa(decimalResult, result, 10);
	return;
}

bool testBigCase()
{
	char* result = malloc(4);
	if (result == NULL)
	{
		return false;
	}
	BinToDecimalString("111110", result);
	bool isOk = strcmp(result, "62") == 0;
	free(result);
	return isOk;
}

bool testSmallCase()
{
	char* result = malloc(4); 
	if (result == NULL)
	{
		return false;
	}
	BinToDecimalString("0", result);
	bool isOk = strcmp(result, "0") == 0;
	free(result);
	return isOk;
}

bool testPowerCase()
{
	char* result = malloc(4);
	if (result == NULL)
	{
		return false;
	}
	BinToDecimalString("100000000", result);
	bool isOk = strcmp(result, "256") == 0;
	free(result);
	return isOk;
}

int main()
{
	if (!testBigCase() || !testPowerCase() || !testSmallCase())
	{
		printf("Tests failed.");
		return -1;
	}
	char inputString[SIZE] = { "" };
	printf("Enter binary number:\n");
	scanf_s("%s", &inputString, SIZE);
	char result[SIZE] = { "" };
	BinToDecimalString(inputString, result);
	printf("Decimal number is:\n%s", result);
	return 0;
}