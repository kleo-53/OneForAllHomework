#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#define ARRAY_SIZE 100
#define RANGE 11
typedef struct PhoneBookEntry {
    char name[30];
    char phone[30];
} PhoneBookEntry;

struct PhoneBookEntry GlobalEntry[ARRAY_SIZE];
int currentRecord = 0;

void clrscr()
{
    system("@cls||clear");
}

int addRecord()
{
    PhoneBookEntry entry;

    printf("\nEnter name and surname: ");
    scanf("%[^\n]%*c", entry.name);

    printf("Enter phone number: ");
    scanf("%[^\n]%*c", entry.phone);
    GlobalEntry[currentRecord] = entry;
    ++currentRecord;
    printf("Record has been added successfully!");
    return 0;
}

int printRecords()
{
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("The file is empty!");
        return 1;
    }
    PhoneBookEntry entry;
    int linesRead = 0;
    if (feof(file))
    {
        printf("\nThe file is empty!");
        fclose(file);
        return 0;
    }
    printf("\nThere are all records in file:");
    while (!feof(file)) {
        char* buffer = malloc(sizeof(char) * 30);
        const int readBytes = fscanf(file, "%[^\n]%*c", buffer);
        if (readBytes < 0) {
            break;
        }
        printf("\n%s", buffer);
        ++linesRead;
    }
    fclose(file);
    return 0;
}

int findNumber()
{
    printf("\nEnter name: ");
    char inputName[30] = "";
    scanf("%[^\n]%*c", inputName);
    PhoneBookEntry entry;

    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("The file is empty!");
        return 1;
    }

    int linesRead = 0;
    bool findUser = false;
    while (!feof(file)) {
        fscanf(file, "%[^:]%*c%*c", entry.name);
        fscanf(file, "%[^\n]%*c", entry.phone);
        if (entry.name < 0 || entry.phone < 0) {
            break;
        }
        if (strcmp(entry.name, inputName) == 0)
        {
            printf("User with name %s has number %s", entry.name, entry.phone);
            findUser = true;
        }
        ++linesRead;
    }
    fclose(file);
    if (!findUser)
    {
        printf("There aren't any records with such name:(");
    }
    return 0;
}

int findName()
{
    printf("\nEnter phone: ");
    char inputNumber[30] = "";
    scanf("%[^\n]%*c", inputNumber);
    PhoneBookEntry entry;

    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("The file is empty!");
        return 1;
    }

    int linesRead = 0;
    bool findUser = false;
    while (!feof(file)) {
        fscanf(file, "%[^:]%*c%*c", entry.name);
        fscanf(file, "%[^\n%]%*c", entry.phone);
        if (entry.name < 0 || entry.phone < 0) {
            break;
        }
        if (strcmp(entry.phone, inputNumber) == 0)
        {
            printf("User with number %s has name %s", entry.phone, entry.name);
            findUser = true;
        }
        ++linesRead;
    }
    fclose(file);
    if (!findUser)
    {
        printf("There aren't any records with such number:(");
    }
    return 0;
}

int saveAll()
{
    FILE* out = fopen("input.txt", "a");
    if (out == NULL) {
        return -1;
    }
    for (int i = 0; i < currentRecord; ++i) 
    {
        fprintf(out, "\n%s: %s", GlobalEntry[i].name, GlobalEntry[i].phone);
    }
    printf("\nRecords has been added to file successfully!");
    fclose(out);
    currentRecord = 0;
    return 0;
}

bool menu()
{
    char command;
    printf("\n0 - Finish work");
    printf("\n1 - Add record (name and number)");
    printf("\n2 - Print all recordinds");
    printf("\n3 - Find number by name");
    printf("\n4 - Find name by number");
    printf("\n5 - Save data in file");
    printf("\nChose the command: ");

    command = getche();
    printf("\n");
    switch (command) {
    case '0':
        return false;
    case '1':
        addRecord();
        break;
    case '2':
        printRecords();
        break;
    case '3':
        findNumber();
        break;
    case '4':
        findName();
        break;
    case '5':
        saveAll();
        break;
    default:
        printf("\nNo option selected");
    }
    return true;
}

int main()
{
    unsigned int sleepTime = 2000;
    while (menu())
    {
        _sleep(sleepTime);
        clrscr();
    }
}