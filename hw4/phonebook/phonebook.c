#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define ARRAY_SIZE 100
#define RANGE 11

typedef struct 
{
    char name[30];
    char phone[30];
} PhoneBookEntry;

void addRecord(PhoneBookEntry *phoneBook, int phoneBookSize)
{
    printf("\nEnter name and surname: ");
    scanf_s("%[^\n]%*c", &phoneBook[phoneBookSize].name, 30);
    printf("Enter phone number: ");
    scanf_s("%[^\n]%*c", &phoneBook[phoneBookSize].phone, 30);
    printf("Record has been added successfully!\n");
}

void printRecords(PhoneBookEntry* phoneBook, int phoneBookSize)
{
    printf("\nThere are all records in database:\n");
    for (int i = 0; i < phoneBookSize; i++)
    {
        printf("%s: %s\n", phoneBook[i].name, phoneBook[i].phone);
    }
}

void findNumber(PhoneBookEntry* phoneBook, int phoneBookSize)
{
    printf("\nEnter name: ");
    char inputName[30] = "";
    scanf_s("%[^\n]%*c", &inputName, 30);

    bool findUser = false;
    for (int i = 0; i < phoneBookSize; ++i)
    {
        if (strcmp(phoneBook[i].name, inputName) == 0)
        {
            printf("User with name %s has number %s\n", phoneBook[i].name, phoneBook[i].phone);
            findUser = true;
        }
    }
    if (!findUser)
    {
        printf("There aren't any records with such name:(\n");
    }
}

void findName(PhoneBookEntry* phoneBook, int phoneBookSize)
{
    printf("\nEnter phone: ");
    char inputNumber[30] = "";
    scanf_s("%[^\n]%*c", &inputNumber, 30);

    bool findUser = false;
    for (int i = 0; i < phoneBookSize; ++i)
    {
        if (strcmp(phoneBook[i].phone, inputNumber) == 0)
        {
            printf("User with name %s has number %s\n", phoneBook[i].name, phoneBook[i].phone);
            findUser = true;
        }
    }
    if (!findUser)
    {
        printf("There aren't any records with such number:(\n");
    }
}

int saveAll(PhoneBookEntry* phoneBook, int phoneBookSize, int addNumber)
{
    FILE* out = fopen("input.txt", "a");
    if (out == NULL) 
    {
        return -1;
    }
    for (int i = phoneBookSize; i < phoneBookSize + addNumber; ++i)
    {
        fprintf(out, "\n%s: %s", phoneBook[i].name, phoneBook[i].phone);
    }
    printf("\nRecords has been added to file successfully!\n");
    fclose(out);
    return 0;
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

    int command = _getche();
    printf("\n");
    switch (command) 
    {
    case '0':
        return -1;
    case '1':
        addRecord(phoneBook, phoneBookSize + addNumber);
        ++addNumber;
        break;
    case '2':
        printRecords(phoneBook, phoneBookSize + addNumber);
        break;
    case '3':
        findNumber(phoneBook, phoneBookSize + addNumber);
        break;
    case '4':
        findName(phoneBook, phoneBookSize + addNumber);
        break;
    case '5':
        saveAll(phoneBook, phoneBookSize, addNumber);
        addNumber = -1000;
        break;
    default:
        printf("\nNo option selected\n");
    }
    return addNumber;
}

int main()
{
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