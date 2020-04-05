#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
void error_exit(char *s);
void countFile(char *fileName);

int totalCountWords = 0;
int totalCountLines = 0;
int totalCountChars = 0;
int countWords = 0;
int countLines = 0;
int countChars = 0;
int fileNameLocation = -1;
bool spaceFound = false;
bool printLines = false;
bool printChar = false;
bool printWord = false;
void print(char *fileName)
{
    printf("  ");
    if (printLines)
    {
        printf("%5d", countLines);
    }

    if (printWord)
    {
        printf("%5d", countWords);
    }
    if (printChar)
    {
        printf("%5d", countChars);
    }

    if (fileName)
    {

        printf(" %5s", fileName);
    }
    printf("\n");
}
void printTotal()
{
    printf("  ");
    if (printLines)
    {
        printf("%5d", totalCountLines);
    }

    if (printWord)
    {
        printf("%5d", totalCountWords);
    }
    if (printChar)
    {
        printf("%5d", totalCountChars);
    }

    if (fileNameLocation != -1)
    {

        printf(" %5s", "Total");
    }
    printf("\n");
}
void count(char character)
{
    if (character != EOF)
    {
        totalCountChars++;
        countChars++;
    }

    if (character == '\n')
    {
        totalCountLines++;
        countLines++;
    }
    if (isspace(character))
    {
        spaceFound = true;
    }
    if (spaceFound && !isspace(character))
    {
        totalCountWords++;
        countWords++;
        spaceFound = false;
    }
}

int main(int argc, char *argv[])
{
    bool noOptions = true;
    bool filePassed = false;

    for (int i = 1; argc >= 2 && i < argc; i++)
    {
        char character = argv[i][0];
        if (character != '-')
        {
            filePassed = true;
        }

        if (character == '-')
        {
            noOptions = false;
            for (int j = 1; argv[i][j] != 0; j++)
            {
                switch (argv[i][j])
                {
                case 'l':
                    printLines = true;
                    break;
                case 'w':
                    printWord = true;
                    break;
                case 'c':
                    printChar = true;
                    break;

                default:
                    break;
                }
            }
        }
        else
        {
            if (noOptions)
            {
                noOptions = true;
            }
        }
    }
    if (noOptions)
    {
        printLines = true;
        printChar = true;
        printWord = true;
    }

    if (argc >= 2 && filePassed)
    {
        int countFiles = 0;
        for (int i = 1; i < argc; i++)
        {

            char firstChar = argv[i][0];
            if (firstChar != '-')
            {

                countFiles++;
                countFile(argv[i]);

            }
        }
        if (countFiles > 1)
        {
            printTotal();
        }
    }
    else
    {
        char character = getchar();
        if (!isspace(character) || isprint(character))
        {
            countWords++;
        }

        while (character != EOF)
        {
            count(character);
            character = getchar();
        }

        print(0);
    }

    return 1;
}

void countFile(char *fileName)
{
    FILE *file;

    file = fopen(fileName, "r");
    char character;

    while (!feof(file))
    {

        character = fgetc(file);
        count(character);
    }

    fclose(file);
    print(fileName);
    countWords = 0;
    countLines = 0;
    countChars = 0;
}

void error_exit(char *s)
{
    fprintf(stderr, "\nERROR: %s - bye!\n", s);
    exit(1);
}