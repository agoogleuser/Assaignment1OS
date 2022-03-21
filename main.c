/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief The SUPER-DOPER BASIC COMMAND SHELL
 * @version 0.1
 * @date 2022-03-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //This is for fork, linux only library.
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAXLIM 256

char lineInput[MAXLIM];
char *command;
char *commandArgs[0xF];

/**Implement these Functions
 * int if_dollar()
 * char **split_line_into_words()
 */

//Do we need a queue?

int if_dollar()
{
    for (int i=0;lineInput[i]!='\0'; i++ )
    {
        if (lineInput[i] == '$')
        {
            lineInput[i] = 0;
            return 1;
        }
    }
    return 0;
}

void zeroIt(int x)
{
    command=NULL;
    for (int i = 0; i<0xF; i++)
        commandArgs[0xF]=NULL;
}

void fixLine()
{
    for (int i=0; lineInput[i] != '\0'; i++)
    {
        if (lineInput[i] == 10)
        {
            lineInput[i] = 0;
        }
    }
}

void splitThisShit()
{
    zeroIt(0);
    int i=0, j=0;
    char commandFlag=0, argFlag=0;
    for (i=0; lineInput[i] != '\n'; i++ )
    {
        if (argFlag==1 && (lineInput[i]== ' ' || lineInput[i] == '\n'))
        {//Gets the command Arguments.
            lineInput[i] = '\0';
            commandArgs[j++]=&lineInput[i+1];
        }
        else if (commandFlag==0 && (lineInput[i]== ' ' || lineInput[i] == '\0'))
        {//gets the command itself
            printf("Stuff1\n");
            commandFlag     = 1;
            argFlag         = 1;
            command         = lineInput;
            commandArgs[j++]= command;
            lineInput[i]    = '\0';
        }
    }
    for (int k=0; k<=j; k++)
    {
        printf("  %s\n", commandArgs[k]);
    }
    zeroIt(j+1);
}

int compareStrings(char *a, char *b)
{
    for (int i=0; ((a[i]!='\0' && b[0]!='\0') && (a[i]!='\n' && b[0]!='\n')) && i<MAXLIM; i++)
    {
        if (a[i]==b[i]) continue;
        else return 0;
    }
    return 1;
}

int main()
{
    pid_t currentFork=1;
    int flag1;
    while (1)
    {
        fgets(lineInput, MAXLIM, stdin);
        fixLine();
        printf("Input: [");
        for (int i = 0; i<20; i++)
            printf("%d ", lineInput[i]);
        printf("\b]\n");
        if (compareStrings(lineInput, "exit")==1)
            exit(0);
        
        else
        {
            currentFork=fork();
            if (currentFork>0)
            {
                printf("Start [%d]\n", currentFork);
                wait(NULL);
            }
            if (currentFork==0) //Child only does it
            {
                splitThisShit();
                if(if_dollar())
                {//execute the command while program working
                    printf("BASH:\n=========\n");
                    execvp(command, commandArgs);
                    exit(0);
                }
                else
                {//Work while waiting for the command to execute
                    printf("BASH:\n=========\n");
                    execvp(command, commandArgs);
                    exit(0);

                }
            }

        }
    }
    return 0;
}