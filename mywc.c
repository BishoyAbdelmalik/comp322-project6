#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
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
void print(char *argv[])
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

    if (fileNameLocation != -1)
    {

        printf(" %5s", argv[fileNameLocation]);
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

            FILE *file;
            char getArgFirstChar = argv[i][0];
            if (getArgFirstChar != '-')
            {
                countFiles++;
                file = fopen(argv[i], "r");
                char character;
                fileNameLocation = i;

                while (!feof(file))
                {

                    character = fgetc(file);
                    count(character);
                }

                fclose(file);
                print(argv);
                countWords = 0;
                countLines = 0;
                countChars = 0;
            }
        }
        if (countFiles>1)
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

        print(argv);
    }

    return 1;
}
