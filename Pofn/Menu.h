#include "Directories/MakeDir.h"
#include <stdbool.h>

bool exitFileExplorer = false;

void commandSwitch(char command[255], char *path)
{
    char *commandName = strtok(command, " ");

    if (strcmp(commandName, "ls") == 0 || strcmp(commandName, "ls\n") == 0)
    {
        displayDirectory(path);
    }
    else if (!strcmp(commandName, "cp") || !strcmp(commandName, "cp\n"))
    {
        char *commandParam = strtok(NULL, " ");
        char *commandParam2 = strtok(NULL, " ");
        char *commandParam3 = strtok(NULL, "\n");
        if (commandParam == NULL || commandParam2 == NULL || commandParam3 == NULL)
        {
            printf("Please enter a valid number of arguments\n");
            return;
        }
        moveFileLocal(0, commandParam, commandParam2, commandParam3);
    }
    else if (!strcmp(commandName, "mv") || !strcmp(commandName, "mv\n"))
    {
        char *commandParam = strtok(NULL, " ");
        char *commandParam2 = strtok(NULL, " ");
        char *commandParam3 = strtok(NULL, "\n");
        if (commandParam == NULL || commandParam2 == NULL || commandParam3 == NULL)
        {
            printf("Please enter a valid number of arguments\n");
            return;
        }

        moveFileLocal(1, commandParam, commandParam2, commandParam3);
    }
    else if (!strcmp(commandName, "ndir") || !strcmp(commandName, "ndir\n"))
    {
        char *commandParam = strtok(NULL, "\n");
        if (commandParam == NULL)
        {
            printf("Please enter a directory path or name\n");
            return;
        }
        int succeed = createDirectory(commandParam);
        if (succeed == 1)
            printf("Invalid directory path or name\n");
        else if (succeed == 2)
            printf("Directory already created\n");
        else
            printf("Directory successfully created\n");
        chdir(commandParam);
    }
    else if (strcmp(commandName, "cd") == 0 || strcmp(commandName, "cd\n") == 0)
    {
        char *commandParam = strtok(NULL, "\n");
        int x = chdir(commandParam);
        if (x)
            printf("Invalid directory name\n");
    }
    else if (strcmp(commandName, "nf") == 0 || strcmp(commandName, "nf\n") == 0)
    {
        char *commandParam = strtok(NULL, " ");
        char *commandParam2 = strtok(NULL, "\n");
        if (commandParam == NULL || commandParam2 == NULL)
        {
            printf("Please enter a valid number of arguments\n");
            return;
        }
        int succeed = createFileLocal(commandParam, commandParam2);
        if (succeed == 1)
            printf("Invalid directory path or name\n");
        else if (succeed == 2)
            printf("Invalid file extension, only create files with .txt extenstion\n");
        else
            printf("File successfully created\n");
    }
    else if (strcmp(commandName, "df") == 0 || strcmp(commandName, "df\n") == 0)
    {
        char *commandParam = strtok(NULL, " ");
        char *commandParam2 = strtok(NULL, "\n");
        if (commandParam == NULL || commandParam2 == NULL)
        {
            printf("Please enter a valid number of arguments\n");
            return;
        }
        int succeed = deleteFile(0, commandParam, commandParam2);
        if (succeed == 1)
        {
            printf("Unable to delete the file\n");
            perror("The following error occurred");
        }
        else
            printf("%s file deleted successfully.\n", commandParam2);
    }
    else if (strcmp(commandName, "rn") == 0 || strcmp(commandName, "rn\n") == 0)
    {
        char *commandParam = strtok(NULL, " ");
        char *commandParam2 = strtok(NULL, " ");
        char *commandParam3 = strtok(NULL, "\n");
        if (commandParam == NULL || commandParam2 == NULL || commandParam3 == NULL)
        {
            printf("Please enter a valid number of arguments\n");
            return;
        }
        int succeed = renameLocal(commandParam, commandParam2, commandParam3);
        if (succeed == 1)
        {
            printf("Unable to open Directory %s\n", commandParam);
            perror("The following error occured");
        }
        else if (succeed == 2)
        {
            printf("File %s could not be found it either isn't in this folder, or doesn't exist", commandParam2);
            return;
        }
        else
            printf("file renamed successfully.\n");
    }
    else if (strcmp(commandName, "textedit") == 0 || strcmp(commandName, "textedit\n") == 0)
    {
        char *commandParam = strtok(NULL, " ");
        char *commandParam2 = strtok(NULL, " ");
        if (commandParam == NULL || commandParam2 == NULL)
        {
            printf("Please enter a valid number of arguments\n");
            return;
        }
        int succeed = editText(commandParam, commandParam2);
        if (succeed == 1)
        {
            printf("Unable to open Directory %s\n", commandParam);
            return;
        }
        else if (succeed == 2)
        {
            printf("File %s does not exist.", commandParam2);
            return;
        }
        else if (succeed == 3)
        {
            printf("Invalid index entered");
            return;
        }
        else
        {
            return;
        }
    }
    else if (strcmp(commandName, "exit") == 0 || strcmp(commandName, "exit\n") == 0)
    {
        exitFileExplorer = true;
    }
    else if (strcmp(commandName, "cat") == 0 || strcmp(commandName, "cat\n") == 0)
    {
        char *CAT = "                      /^--^\\     /^--^\\     /^--^\\ \n                      \\____/     \\____/     \\____/ \n                     /      \\   /      \\   /      \\ \nKAT                 |        | |        | |        | \n                     \\__  __/   \\__  __/   \\__  __/ \n|^|^|^|^|^|^|^|^|^|^|^|^\\ \\^|^|^|^/ /^|^|^|^|^\\ \\^|^|^|^|^|^|^|^|^|^|^|^| \n| | | | | | | | | | | | |\\ \\| | |/ /| | | | | |\\ \\| | | | | | | | | | | | \n########################/ /######\\ \\###########/ /####################### \n| | | | | | | | | | | | \\/| | | | \\/| | | | | |\\/ | | | | | | | | | | | | \n|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|\n";

        for (int i = 0; i < 638; i++)
        {
            printf("%c", CAT[i]);
        }
    }
    else if (strcmp(commandName, "dog") == 0 || strcmp(commandName, "dog\n") == 0)
    {
        char *DOG = "         ,--._______,-. \n       ,\',\'  ,    .  ,_`-. \n      / /  ,\' , _` ``. |  )       `-.. \n     (,\';\'\"\"`/ \'\"`-._ ` \\/ ______    \\\\ \n       : ,o.-`- ,o.  )` -\'      `---.)) \n       : , d8b ^-.   \'|   `.      `    `. \n       |/ __:_     `. |  ,  `       `    \\ \n       | ( ,-.`-.    ;\'  ;   `       :    ; \n       | |  ,   `.      /     ;      :    \\ \n       ;-\'`:::._,`.__),\'             :     ; \n      / ,  `-   `--                  ;     | \n     /  \\                   `       ,      | \n    (    `     :              :    ,\\      | \n     \\   `.    :     :        :  ,\'  \\    : \n      \\    `|-- `     \\ ,\'    ,-\'     :-.-\'; \n      :     |`--.______;     |        :    : \n       :    /           |    |         |   \\ \n       |    ;           ;    ;        /     ; \n     _/--\' |   -hrr-   :`-- /         \\_:_:_| \n   ,\',\',\'  |           |___ \\ \n   `^._,--\'           / , , .) \n                      `-._,-\' \n";

        for (int i = 0; i < 908; i++)
        {
            printf("%c", DOG[i]);
        }
    }
    else if (strcmp(commandName, "help") == 0 || strcmp(commandName, "help\n") == 0)
    {
        String DISCRIPTION = createString();
        String USAGE = createString();
        int flag = 0;
        char *next = strtok(NULL, "\n");
        if (next == NULL)
        {
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
            flag = 1;
        }
        else if (strcmp(next, "mv") == 0)
        {
            scanString(DISCRIPTION, "Move a file from dir x to dir y");
            scanString(USAGE, "mv SOURCE DESTINATION FILENAME");
        }
        else if (strcmp(next, "cp") == 0)
        {
            scanString(DISCRIPTION, "Copy a file from dir x to dir y");
            scanString(USAGE, "cp SOURCE DESTINATION FILENAME");
        }
        else if (strcmp(next, "ls") == 0)
        {
            scanString(DISCRIPTION, "List all files in the current directitory");
            scanString(USAGE, "ls");
        }
        else if (strcmp(next, "ndir") == 0)
        {
            scanString(DISCRIPTION, "Create a new directitory");
            scanString(USAGE, "ndir DIR_PATH");
        }
        else if (strcmp(next, "cd") == 0)
        {
            scanString(DISCRIPTION, "Change the directitory");
            scanString(USAGE, "cd DIR_PATH");
        }
        else if (strcmp(next, "nf") == 0)
        {
            scanString(DISCRIPTION, "Create a NewFile");
            scanString(USAGE, "nf DIR_PATH FILENAME");
        }
        else if (strcmp(next, "df") == 0)
        {
            scanString(DISCRIPTION, "Delete a File");
            scanString(USAGE, "df DIR_PATH FILENAME");
        }
        else if (strcmp(next, "rn") == 0)
        {
            scanString(DISCRIPTION, "Rename a File");
            scanString(USAGE, "rn DIR_PATH FILENAME NEW_FILENAME");
        }
        else if (strcmp(next, "textedit") == 0)
        {
            scanString(DISCRIPTION, "Edit a textfile");
            scanString(USAGE, "textedit SOURCE FILENAME");
        }
        else
        {
            printf("Invalid help command\n");
            flag = 1;
        }

        if (flag == 0)
        {
            printf("*****************HELP*****************\n");
            printf("COMMAND \t%s \n", next);
            printf("DESCRIPTION: \t%s\n", putString(DISCRIPTION));
            printf("USAGE: \t\t%s\n", putString(USAGE));
            printf("**************************************\n");
        }
    }
    else
    {
        printf("Please enter a valid command!\n");
    }
}

int menuStart()
{
    char *currPath = currentDirectory();

    char command[100];
    while (!exitFileExplorer)
    {
        printf("%s :/> ", currPath);
        fgets(command, 255, stdin);
        commandSwitch(command, currPath);
        currPath = currentDirectory();
    }
    return 0;
}