// main C code is written here:

#include <iostream>
#include <unistd.h> //Has the Fork() and w
#include <string.h>
#include <sys/wait.h>
using namespace std;

/*void  stringArr_to_charArr(char *output[255], string input)
{//Not sure if this function works
    int i,j=0; //counter for input arguments.
    int position=0;
    for (i=0; input[i]!='\0' && input[i]!='\n'; i++)
    {
        if (input[i]==' ')
        {
            strcpy(output[j], input.substr(position, i-1).c_str());
            position=i+1;
            j++;
        }
    }

    //Adding the last argument
    strcpy(output[j++], input.substr(position,i).c_str());
    //Adding a NULL address in the end of the output
    *output[j]=NULL;
}*/

char **stringArr_to_charArr(string input, int *words_num)
{
    char **output = (char **)calloc(16, sizeof(char *));
    int i = 0, j = 0, pos = 0, size = input.length();
    string debugString;
    //         0123456789abcdefgh"
    // input = "This is an example"
    for (i = 0; i <= size; i++)
    {
        if (input[i] == ' ' || input[i] == '\0')
        {
            output[j] = (char *)malloc((i - pos) * sizeof(char));
            strcpy(output[j], input.substr(pos, i - pos).c_str());
            debugString.insert(0, input.substr(pos, i - pos));
            pos = i + 1;
            j++;
        }
    }
    *words_num = j;
    // output={"this", "is", "an", "example", NULL}
    return output;
}

int main()
{
    int process_id;
    int wordSize;

    string Line_Input;
    string command;
    // char commandArguments[0x10][0xFF];
    char **commandArguments = NULL; // Dynamically allocating a 2D array, the C++ way
    char *x[10] = {"pwd", NULL};
    /*
    parent =17;

    fork
    child1=1;

    */
   int flag=0;
    while (1)
    {
        Line_Input="0";

        cout << "Current Directory: " << endl << '\b';
        process_id = fork();
        if (process_id == 0) // means child 
        {
            execvp("pwd", x);
            exit(0);
        }
        else
            wait(NULL);

        // 1. Check if the input from user was "exit"
        getline(cin, Line_Input);
        char check = Line_Input.back();
        //int lastCharacterP = Line_Input.end();; 

        if (Line_Input == "exit")
            break;

        // If not,
        // 2. The program will split the input to many strings in
        // order to use the input as an input in execvp()

        command.assign(Line_Input.substr(0, Line_Input.find(" ")));

        commandArguments = stringArr_to_charArr(Line_Input, &wordSize);
        char **output = (char **)calloc(16, sizeof(char *));
        process_id = fork();
        //"cd" "/home/kurama/Downloads"
        if (process_id == 0)
        {
            if (command=="cd")
            {
                chdir (*((commandArguments)+1));
                flag=1;
                cout << "Directory changed\n\n";

                if (process_id!=0)  exit(0);
            }
            else
            {
                execvp(command.c_str(), commandArguments);
                exit(0);
            }
        }
        else if (process_id != 0 && check != '&')
        {
            cout << "Waiting\n";
            wait(NULL);
        }
        //if (flag!=0) exit(0);
        // Testing Area
        // TODO: Free commandArguments

        for (int i = 0; i < wordSize; i++)
            free(*(commandArguments + i));

        free(commandArguments);
    }
    cout << "Exiting...\n\n";

    return 0;
}