// main C code is written here:

#include <iostream>
#include <unistd.h> //Has the Fork() and w
#include <string.h>
#include <sys/wait.h>
using namespace std;

char **stringArr_to_charArr(string input, int *words_num)
{
    char **output = (char **)calloc(16, sizeof(char *));
    int i = 0, j = 0, pos = 0, size = input.length();
    string debugString; //used for debugger only, remove it for release.
    //             0123456789abcdefgh
    // ->>input = "This is an example"
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
    // ->>output={"this", "is", "an", "example", NULL}
    return output;
}

bool check_and_symbol(string input)
{
    for (int i=input.length()-1; i>=0; i--)
    {
        if (input[i]== ' ') continue;
        if (input[i]== '&') return true;
        else                 break;
    }
    return false;
}

int main()
{
    int process_id;
    int wordSize;
    string Line_Input;
    string command;
    char currentDirectory[0xFF]; //Stores the current directory string
    char **commandArguments = NULL;
    bool exitFlag=0;

    cout << "Starting our basic shell:\n++++++++++++++++++++++++++\n";
    while (1)
    {
        Line_Input = "0";//resets the input buffer.
        getcwd(currentDirectory, 0xFF); //Calls a system function to get the current working directory.
        cout << currentDirectory << "$ "; 

        // 0. Getting Input Buffer from the user in the terminal.
        getline(cin, Line_Input);
        bool check = check_and_symbol(Line_Input); //check if there was an & at the end of the line
        if (check==true){
            Line_Input.erase(Line_Input.find_last_of('&')); //removes &
            Line_Input.erase(Line_Input.end()-1);//removes extra space.
        }
       
        // 1. Check if the input from user was "exit"
        if (Line_Input == "exit")   break;

        // 2. Split the input biffer using the following two lines
        command.assign(Line_Input.substr(0, Line_Input.find(" ")));
        commandArguments = stringArr_to_charArr(Line_Input, &wordSize);

        // 3. Check if the input was "cd"
        if (command == "cd")
        {
            chdir(*((commandArguments) + 1));
            goto FreeStuff;//restarts the loop.
        }
        
        //Executing General commands
        process_id = fork();
        if (process_id == 0)
        {//Child Process goes here.
            execvp(command.c_str(), commandArguments);
            exit(0);
        }
        else if (process_id != 0 && check == false)
        {//Parent process goes here
            wait(NULL); //Wait for all children to die. (don't take this comment literally pls)
        }
FreeStuff:
        // Free commandArgumentf from memory every loop.
        for (int i = 0; i < wordSize; i++)
            free(*(commandArguments + i));

        free(commandArguments);
    }

    cout << "Exiting...\n+++++++++++++++++++++++++++++++++++++++++++++\n";
    return 0;
}