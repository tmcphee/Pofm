#include "Directories/MakeDir.h"
#include <stdbool.h>

//flag to know when to exit pofn
bool exitFileExplorer = false;
//repeat path flag
bool repeatPathFlag = true;

//switch function for command
void commandSwitch(char command[255], char *path)
{
    //gets the first word entered. this is the command name
    char *commandName = strtok(command, " ");

    //if the command is ls
    if (strcmp(commandName, "ls") == 0 || strcmp(commandName, "ls\n") == 0)
    {
        //display the current directory
        displayDirectory(path);
    }
    //if the command is cp
    else if (!strcmp(commandName, "cp") || !strcmp(commandName, "cp\n"))
    {
        //get the next 3 words
        char *commandParam = strtok(NULL, " ");
        char *commandParam2 = strtok(NULL, " ");
        char *commandParam3 = strtok(NULL, "\n");
        //if any of them are null
        if (commandParam == NULL || commandParam2 == NULL || commandParam3 == NULL)
        {
            //error
            //please print valid args
            printf("Please enter a valid number of arguments\n");
            return;
        }
        //else copy local file
        moveFileLocal(0, commandParam, commandParam2, commandParam3);
    }
    //if command is mv
    else if (!strcmp(commandName, "mv") || !strcmp(commandName, "mv\n"))
    {
        //get next 3 words
        char *commandParam = strtok(NULL, " ");
        char *commandParam2 = strtok(NULL, " ");
        char *commandParam3 = strtok(NULL, "\n");
        //if any of them are null
        if (commandParam == NULL || commandParam2 == NULL || commandParam3 == NULL)
        {
            //error
            //print valid number args
            printf("Please enter a valid number of arguments\n");
            return;
        }

        //mv file loval
        moveFileLocal(1, commandParam, commandParam2, commandParam3);
    }
    //if command is ndir
    else if (!strcmp(commandName, "ndir") || !strcmp(commandName, "ndir\n"))
    {
        //get next arg
        char *commandParam = strtok(NULL, "\n");
        //if null
        if (commandParam == NULL)
        {
            //error
            //please enter valid num arg
            printf("Please enter a directory path or name\n");
            return;
        }
        //try to create a new directory
        int succeed = createDirectory(commandParam);
        //if 2
        if (succeed == 2)
            //error
            printf("Directory already created\n");
        //if neither
        else
            //succeed
            printf("Directory successfully created\n");
        //change current directory to be the arguement
        chdir(commandParam);
    }
    //if command is cd
    else if (strcmp(commandName, "cd") == 0 || strcmp(commandName, "cd\n") == 0)
    {
        //get next arg
        char *commandParam = strtok(NULL, "\n");
        //if null
        if (commandParam == NULL)
        {
            //error
            //please enter valid num arg
            printf("Please enter a directory path or name\n");
            return;
        }
        //try to change dir
        int x = chdir(commandParam);
        //if failed
        if (x)
            //error
            printf("Invalid directory name\n");
    }
    //if command is nf
    else if (strcmp(commandName, "nf") == 0 || strcmp(commandName, "nf\n") == 0)
    {
        //get next 2 args
        char *commandParam = strtok(NULL, " ");
        char *commandParam2 = strtok(NULL, "\n");
        //if any args are null
        if (commandParam == NULL || commandParam2 == NULL)
        {
            //error
            printf("Please enter a valid number of arguments\n");
            return;
        }
        //try to create new file
        int succeed = createFileLocal(commandParam, commandParam2);
        //if 1
        if (succeed == 1)
            //error
            printf("Invalid directory path or name\n");
        //if 2
        else if (succeed == 2)
            //error
            printf("Invalid file extension, only create files with .txt extenstion\n");
        //if 0
        else
            //succeed
            printf("File successfully created\n");
    }
    //if command is df
    else if (strcmp(commandName, "df") == 0 || strcmp(commandName, "df\n") == 0)
    {
        //get next 2 args
        char *commandParam = strtok(NULL, " ");
        char *commandParam2 = strtok(NULL, "\n");
        //if any are null
        if (commandParam == NULL || commandParam2 == NULL)
        {
            //error
            printf("Please enter a valid number of arguments\n");
            return;
        }
        //try to delete file
        int succeed = deleteFile(0, commandParam, commandParam2);
        //if 1
        if (succeed == 1)
        {
            //error
            printf("Unable to delete the file\n");
            perror("The following error occurred");
        }
        //if 0
        else
            //succeed
            printf("%s file deleted successfully.\n", commandParam2);
    }
    //if command is rn
    else if (strcmp(commandName, "rn") == 0 || strcmp(commandName, "rn\n") == 0)
    {
        //get next 3 args
        char *commandParam = strtok(NULL, " ");
        char *commandParam2 = strtok(NULL, " ");
        char *commandParam3 = strtok(NULL, "\n");
        //if any are null
        if (commandParam == NULL || commandParam2 == NULL || commandParam3 == NULL)
        {
            //error
            printf("Please enter a valid number of arguments\n");
            return;
        }
        //try to rename file
        int succeed = renameLocal(commandParam, commandParam2, commandParam3);
        //if 1
        if (succeed == 1)
        {
            //error
            printf("Unable to open Directory %s\n", commandParam);
            perror("The following error occured");
        }
        //if 2
        else if (succeed == 2)
        {
            //error
            printf("File %s could not be found it either isn't in this folder, or doesn't exist\n", commandParam2);
            return;
        }
        //if 0
        else
            //succeed
            printf("file renamed successfully.\n");
    }
    //if command is textedit
    else if (strcmp(commandName, "textedit") == 0 || strcmp(commandName, "textedit\n") == 0)
    {
        //get next 2 arg
        char *commandParam = strtok(NULL, " ");
        char *commandParam2 = strtok(NULL, "\n");
        //if any are null
        if (commandParam == NULL || commandParam2 == NULL)
        {
            //error
            printf("Please enter a valid number of arguments\n");
            return;
        }
        //try to edit text
        int succeed = editText(commandParam, commandParam2);
        //if 1
        if (succeed == 1)
        {
            //error
            printf("Unable to open Directory %s\n", commandParam);
            return;
        }
        //if 2
        else if (succeed == 2)
        {
            //error
            printf("File %s does not exist.\n", commandParam2);
            return;
        }
        //if 3
        else if (succeed == 3)
        {
            //error
            printf("Invalid index entered\n");
            return;
        }
        //if 0
        else
        {
            //succeed
            return;
        }
    }
    //if command is exit
    else if (strcmp(commandName, "exit") == 0 || strcmp(commandName, "exit\n") == 0)
    {
        //set exit flag to be true
        exitFileExplorer = true;
    }
    //if command is cat
    else if (strcmp(commandName, "cat") == 0 || strcmp(commandName, "cat\n") == 0)
    {
        //initialize cat ascii art
        char *CAT = "                      /^--^\\     /^--^\\     /^--^\\ \n                      \\____/     \\____/     \\____/ \n                     /      \\   /      \\   /      \\ \nKAT                 |        | |        | |        | \n                     \\__  __/   \\__  __/   \\__  __/ \n|^|^|^|^|^|^|^|^|^|^|^|^\\ \\^|^|^|^/ /^|^|^|^|^\\ \\^|^|^|^|^|^|^|^|^|^|^|^| \n| | | | | | | | | | | | |\\ \\| | |/ /| | | | | |\\ \\| | | | | | | | | | | | \n########################/ /######\\ \\###########/ /####################### \n| | | | | | | | | | | | \\/| | | | \\/| | | | | |\\/ | | | | | | | | | | | | \n|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|\n";

        //print cat
        for (int i = 0; i < 638; i++)
        {
            printf("%c", CAT[i]);
        }
    }
    //if command is dog
    else if (strcmp(commandName, "dog") == 0 || strcmp(commandName, "dog\n") == 0)
    {
        //initialize dog ascii art
        char *DOG = "         ,--._______,-. \n       ,\',\'  ,    .  ,_`-. \n      / /  ,\' , _` ``. |  )       `-.. \n     (,\';\'\"\"`/ \'\"`-._ ` \\/ ______    \\\\ \n       : ,o.-`- ,o.  )` -\'      `---.)) \n       : , d8b ^-.   \'|   `.      `    `. \n       |/ __:_     `. |  ,  `       `    \\ \n       | ( ,-.`-.    ;\'  ;   `       :    ; \n       | |  ,   `.      /     ;      :    \\ \n       ;-\'`:::._,`.__),\'             :     ; \n      / ,  `-   `--                  ;     | \n     /  \\                   `       ,      | \n    (    `     :              :    ,\\      | \n     \\   `.    :     :        :  ,\'  \\    : \n      \\    `|-- `     \\ ,\'    ,-\'     :-.-\'; \n      :     |`--.______;     |        :    : \n       :    /           |    |         |   \\ \n       |    ;           ;    ;        /     ; \n     _/--\' |   -hrr-   :`-- /         \\_:_:_| \n   ,\',\',\'  |           |___ \\ \n   `^._,--\'           / , , .) \n                      `-._,-\' \n";

        //print dog
        for (int i = 0; i < 908; i++)
        {
            printf("%c", DOG[i]);
        }
    }
    //if command is help
    else if (strcmp(commandName, "help") == 0 || strcmp(commandName, "help\n") == 0)
    {
        //create description string
        String DISCRIPTION = createString();
        //create usage string
        String USAGE = createString();
        //set help flag
        int flag = 0;
        //get next arguement
        char *next = strtok(NULL, "\n");
        //if null
        if (next == NULL)
        {
            //print all help functions
            printf("*****************HELP*****************\n");
            printf("(Use the following commands for targeted help)\n");
            printf("help mv \t--->\t Move a file\n");
            printf("help cp \t--->\t Copy a file\n");
            printf("help ls \t--->\t List files in directitory\n");
            printf("help ndir \t--->\t Create a new Directitory\n");
            printf("help cd \t--->\t Change the Directitory\n");
            printf("help nf \t--->\t Create a NewFile\n");
            printf("help df \t--->\t Delete File\n");
            printf("help rn \t--->\t Rename File\n");
            printf("help textedit \t--->\t Edit a TextFile\n");
            printf("help exit \t--->\t Exit the Application\n");
            printf("**************************************\n");
            //set help flag to be 1
            flag = 1;
        }
        //if mv
        else if (strcmp(next, "mv") == 0)
        {
            //set strings to mv
            scanString(DISCRIPTION, "Move a file from dir x to dir y");
            scanString(USAGE, "mv SOURCE DESTINATION FILENAME");
        }
        //if cp
        else if (strcmp(next, "cp") == 0)
        {
            //set strings to cp
            scanString(DISCRIPTION, "Copy a file from dir x to dir y");
            scanString(USAGE, "cp SOURCE DESTINATION FILENAME");
        }
        //if ls
        else if (strcmp(next, "ls") == 0)
        {
            //set strings to ls
            scanString(DISCRIPTION, "List all files in the current directitory");
            scanString(USAGE, "ls");
        }
        //if ndir
        else if (strcmp(next, "ndir") == 0)
        {
            //set strings to ndir
            scanString(DISCRIPTION, "Create a new directitory");
            scanString(USAGE, "ndir DIR_PATH");
        }
        //if cd
        else if (strcmp(next, "cd") == 0)
        {
            //set strings to cd
            scanString(DISCRIPTION, "Change the directitory");
            scanString(USAGE, "cd DIR_PATH");
        }
        //if nf
        else if (strcmp(next, "nf") == 0)
        {
            //set strings to nf
            scanString(DISCRIPTION, "Create a NewFile");
            scanString(USAGE, "nf DIR_PATH FILENAME");
        }
        //if df
        else if (strcmp(next, "df") == 0)
        {
            //set strings to df
            scanString(DISCRIPTION, "Delete a File");
            scanString(USAGE, "df DIR_PATH FILENAME");
        }
        //if rn
        else if (strcmp(next, "rn") == 0)
        {
            //set strings to rn
            scanString(DISCRIPTION, "Rename a File");
            scanString(USAGE, "rn DIR_PATH FILENAME NEW_FILENAME");
        }
        //if textedit
        else if (strcmp(next, "textedit") == 0)
        {
            //set strings to textedit
            scanString(DISCRIPTION, "Edit a textfile");
            scanString(USAGE, "textedit SOURCE FILENAME");
        }
        //if exit
        else if (strcmp(next, "exit") == 0)
        {
            //set strings to exit
            scanString(DISCRIPTION, "Exits the application");
            scanString(USAGE, "exit");
        }
        //if none of the above
        else
        {
            //invalid command
            printf("Invalid help command\n");
            //help flag is 1
            flag = 1;
        }

        //if flag is 0, only 0 if theres a valid second arg
        if (flag == 0)
        {
            //print help function of second arg
            printf("*****************HELP*****************\n");
            printf("COMMAND \t%s \n", next);
            printf("DESCRIPTION: \t%s\n", putString(DISCRIPTION));
            printf("USAGE: \t\t%s\n", putString(USAGE));
            printf("**************************************\n");
        }
    }
    //if empty command
    else if (strcmp(commandName, "\n") == 0 | strcmp(commandName, " \n") == 0)
        //dont repeat the path
        repeatPathFlag = false;
    //defaut
    else
    {
        //invalid command
        printf("Please enter a valid command!\n");
    }
}

//start the menu
int menuStart()
{
    //get path to current directory
    char *currPath = currentDirectory();

    //allocate command string
    char command[255];
    //while exit flag is not set
    while (!exitFileExplorer)
    {
        //if repeatpathflag is set
        if (repeatPathFlag == true)
            //repeat path
            printf("%s :/> ", currPath);
        //set repeat path flag to 1
        repeatPathFlag = true;
        //get command
        fgets(command, 255, stdin);
        //switch statement for command
        commandSwitch(command, currPath);
        //get currpath
        currPath = currentDirectory();
    }
    //return
    return 0;
}