#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h> 
void error_exit(char *s);
void countFile(char *fileName, int pipe[]);
int readpipe(int mypipe[]);
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
void print(char *fileName, int PID)
{
    printf("  ");
    totalCountLines+=countLines;
    totalCountWords+=countWords;
    totalCountChars+=countChars;
    if (printLines)
    {
        printf("%10d", countLines);
    }
    if (printWord)
    {
        printf("%10d", countWords);
    }
    if (printChar)
    {
        printf("%10d", countChars);
    }
    if (fileName)
    {
        printf(" %5s", fileName);
    }
    printf(" %d",PID);
    printf("\n");
}
void printTotal()
{
    printf("  ");
    if (printLines)
    {
        printf("%10d", totalCountLines);
    }

    if (printWord)
    {
        printf("%10d", totalCountWords);
    }
    if (printChar)
    {
        printf("%10d", totalCountChars);
    }

   

    printf(" %5s", "Total");

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

                int mypipe[2];
                if (pipe(mypipe) == -1)
                {
                    error_exit("pipe() failed");
                }
                int forkValue;
                if ((forkValue = fork()) == 0)
                {
                    close(mypipe[0]);// close read
                    countFile(argv[i], mypipe);
                    return 0;
                }
                if (forkValue > 0)
                {
                    printf("parent Child PID %d\n",forkValue);

                    int PID=readpipe(mypipe);
                    print(argv[i],PID);
                }
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

        print(0,0);//fornow
    }

    return 1;
}

void countFile(char *fileName, int mypipe[])
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
    int values[3] = {countWords, countLines, countChars};
    if (write(mypipe[1], values, sizeof(values) ) == -1)
    {
        error_exit("write() failed");
    }
    close(mypipe[1]);// close write
    
}
int readpipe(int mypipe[])
{
    close(mypipe[1]);// close write
  
    // Wait for child to send a string 
    int PID=wait(NULL);
    int values[3];
    if (read(mypipe[0], values, sizeof(values) ) == -1)
    {
        error_exit("read() failed");
    }
    countWords = values[0];
    countLines = values[1];
    countChars = values[2];
       
    close(mypipe[0]);// close read
    return PID;

}

void error_exit(char *s)
{
    fprintf(stderr, "\nERROR: %s - bye!\n", s);
    exit(1);
}