//main C code is written here:

#include <iostream>
#include <unistd.h> //Has the Fork() and w
#include <string.h>
using namespace std;


void  stringArr_to_charArr(char *output[255], string input)
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
}

int main()
{
    int process_id;

    string Line_Input;
    string command;
    //char commandArguments[0x10][0xFF];
    char **commandArguments = new char*[0x10]; //Dynamically allocating a 2D array, the C++ way
    char *x[10]={"pwd", NULL};
    while(1)
    {
        process_id = fork();
        if (process_id == 0)    execvp("pwd", x);
        cout << "\\>>>";
        getline(cin, Line_Input);

        //1. Check if the input from user was "exit"
        if (Line_Input == "exit")
            break;
        
        // If not, 
        // 2. The program will split the input to many strings in 
        // order to use the input as an input in execvp()
        
        command.assign(Line_Input.substr(0,Line_Input.find(" ")));
        
        stringArr_to_charArr(commandArguments, Line_Input);
        

        //Testing Area

        cout << command << endl;

        cout << "Arguments:\n";    
    }
    cout << "Exiting...\n\n";
    for(int i = 0; i < 0x10; i++)   delete[] commandArguments[i];
    delete[] commandArguments;

return 0;
}