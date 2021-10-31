#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE 100
#define RANGE 11

typedef struct 
{
    char name[30];
    char phone[30];
} PhoneBookEntry;

void findUser(const char* inputName, const PhoneBookEntry* phoneBook, int phoneBookSize, PhoneBookEntry* answer, int* counterUser)
{
    for (int i = 0; i < phoneBookSize; ++i)
    {
        if (strcmp(phoneBook[i].name, inputName) == 0)
        {
            answer[*counterUser] = phoneBook[i];
            *counterUser = *counterUser + 1;
        }
    }
}

void findNumber(char* inputNumber, PhoneBookEntry* phoneBook, int phoneBookSize, PhoneBookEntry* answer, int* counterUser)
{
    for (int i = 0; i < phoneBookSize; ++i)
    {
        if (strcmp(phoneBook[i].phone, inputNumber) == 0)
        {
            answer[*counterUser] = phoneBook[i];
            *counterUser = *counterUser + 1;
        }
    }
}

int saveAll(FILE* out, PhoneBookEntry* phoneBook, int phoneBookSize, int addNumber)
{
    if (out == NULL) 
    {
        return -1;
    }
    for (int i = phoneBookSize; i < phoneBookSize + addNumber; ++i)
    {
        fprintf(out, "\n%s: %s", phoneBook[i].name, phoneBook[i].phone);
    }
    fclose(out);
    return 0;
}

void printFindResults(const char* founder, PhoneBookEntry* answerBook, int counterUser)
{
    if (counterUser == 0)
    {
        printf("There aren't any records with such %s:(\n", founder);
    }
    else
    {
        for (int i = 0; i < counterUser; ++i)
        {
            printf("User with name %s has number %s\n", answerBook[i].name, answerBook[i].phone);
        }
    }
}

int menu(PhoneBookEntry *phoneBook, int phoneBookSize, int addNumber)
{
    printf("\n0 - Finish work");
    printf("\n1 - Add record (name and number)");
    printf("\n2 - Print all recordinds");
    printf("\n3 - Find number by name");
    printf("\n4 - Find name by number");
    printf("\n5 - Save data in file");
    printf("\nChose the command: ");

    char command = ' ';
    scanf_s("%c", &command, 2);
    printf("\n");
    switch (command)
    {
    case '0':
        return -1;
    case '1':
    {
        phoneBookSize = phoneBookSize + addNumber;
        printf("\nEnter name and surname: ");
        scanf_s("%*c%[^\n]", &phoneBook[phoneBookSize].name, 30);
        printf("Enter phone number: ");
        scanf_s("%*c%[^\n]%*c", &phoneBook[phoneBookSize].phone, 30);
        ++addNumber;
        printf("Record has been added successfully!\n");
        break;
    }
    case '2':
    {
        scanf_s("%*c");
        phoneBookSize = phoneBookSize + addNumber;
        printf("\nThere are all records in database:\n");
        for (int i = 0; i < phoneBookSize; i++)
        {
            printf("%s: %s\n", phoneBook[i].name, phoneBook[i].phone);
        }
        break;
    }
    case '3':
    {
        printf("\nEnter name: ");
        char inputName[30] = "";
        scanf_s("%*c%[^\n]%*c", &inputName, 30);
        PhoneBookEntry answerBook[100];
        int counterUser = 0;
        findUser(inputName, phoneBook, phoneBookSize + addNumber, answerBook, &counterUser);
        printFindResults("name", answerBook, counterUser);
        break;
    }
    case '4':
    {
        printf("\nEnter phone: ");
        char inputNumber[30] = "";
        scanf_s("%*c%[^\n]%*c", &inputNumber, 30);
        PhoneBookEntry answerBook[100];
        int counterUser = 0;
        findNumber(inputNumber, phoneBook, phoneBookSize + addNumber, answerBook, &counterUser);
        printFindResults("phone", answerBook, counterUser);
        break;
    }
    case '5':
    {
        scanf_s("%*c");
        FILE* out = fopen("input.txt", "a");
        saveAll(out, phoneBook, phoneBookSize, addNumber);
        fclose(out);
        printf("\nRecords has been added to file successfully!\n");
        addNumber = -1000;
        break;
    }
    default:
        printf("\nNo option selected\n");
    }
    return addNumber;
}

bool testCase()
{
    FILE* file = fopen("test.txt", "r");
    if (file == NULL)
    {
        return false;
    }
    int linesRead = 0;
    PhoneBookEntry phoneBook[100];
    while (!feof(file))
    {
        fscanf_s(file, "%[^:]%*c%*c", &phoneBook[linesRead].name, 30);
        fscanf_s(file, "%[^\n%]%*c", &phoneBook[linesRead].phone, 30);
        ++linesRead;
    }
    fclose(file);
    strcpy(&phoneBook[linesRead].name, "abca abcda");
    strcpy(&phoneBook[linesRead].phone, "11234");
    int addNumber = 1;
    strcpy(&phoneBook[linesRead + addNumber].name, "qwwe");
    strcpy(&phoneBook[linesRead + addNumber].phone, "2341");
    ++addNumber;

    FILE* out = fopen("test.txt", "a");
    saveAll(out, phoneBook, linesRead, addNumber);
    fclose(out);
    FILE* file2 = fopen("test.txt", "r");
    if (file2 == NULL)
    {
        return false;
    }
    PhoneBookEntry element[1];
    linesRead = 0;
    while (!feof(file))
    {
        fscanf_s(file2, "%[^:]%*c%*c", &element[0].name, 30);
        fscanf_s(file2, "%[^\n%]%*c", &element[0].phone, 30);
        if (strcmp(&phoneBook[linesRead], &element[0]) != 0)
        {
            return false;
        }
        ++linesRead;
    }
    fclose(file);

    PhoneBookEntry testBook[4];
    strcpy(&testBook[0].name, "Qwerty");
    strcpy(&testBook[0].phone, "123");
    int testCounter = 1;
    char testName[30] = "Qwerty";
    PhoneBookEntry answerBook[4];
    int counterUser = 0;
    findUser(testName, phoneBook, linesRead + addNumber, answerBook, &counterUser);
    if (counterUser != testCounter || strcmp(&answerBook[0], &testBook[0]) != 0)
    {
        return false;
    }
    strcpy(testName, "aaaaa");
    testCounter = 0;
    counterUser = 0;
    findUser(testName, phoneBook, linesRead + addNumber, answerBook, &counterUser);
    if (counterUser != testCounter)
    {
        return false;
    }
    char testPhone[30] = "111";
    testCounter = 2;
    strcpy(&testBook[0].name, "qwe");
    strcpy(&testBook[0].phone, "111");
    strcpy(&testBook[1].name, "One Two");
    strcpy(&testBook[1].phone, "111");
    findNumber(testPhone, phoneBook, linesRead + addNumber, answerBook, &counterUser); 
    if (counterUser != testCounter || strcmp(&answerBook[0], &testBook[0]) != 0 || strcmp(&answerBook[1], &testBook[1])!= 0)
    {
        return false;
    }
    
    return true;
}

int main()
{
    if (!testCase())
    {
        printf("Tests failed:(");
        return -1;
    }
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) 
    {
        printf("The file is empty!\n");
        return 1;
    }
    int linesRead = 0;
    PhoneBookEntry phoneBook[100];
    while (!feof(file)) 
    {
        fscanf_s(file, "%[^:]%*c%*c", &phoneBook[linesRead].name, 30);
        fscanf_s(file, "%[^\n%]%*c", &phoneBook[linesRead].phone, 30);
        ++linesRead;
    }
    fclose(file);
    int addNumber = 0;
    int result = menu(phoneBook, linesRead, addNumber);
    while (result != -1)
    {
        if (result == -1000)
        {
            linesRead += addNumber;
            addNumber = 0;
        }
        else
        {
            addNumber = result;
        }
        result = menu(phoneBook, linesRead, addNumber);
    }
}