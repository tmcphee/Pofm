#include "Directories/MakeDir.h"
#include <stdbool.h>

bool exitFileExplorer = false;

void commandSwitch(char command[100], char *path)
{
    char *commandName = strtok(command, " ");

    if (strcmp(commandName, "Directory") == 0 || strcmp(commandName, "Directory\n") == 0)
    {
        displayDirectory(path);
    }
    else if (!strcmp(commandName, "NewDirectory") || !strcmp(commandName, "NewDirectory\n"))
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
    else if (strcmp(commandName, "ChangeDirectory") == 0 || strcmp(commandName, "ChangeDirectory\n") == 0)
    {
        char *commandParam = strtok(NULL, "\n");
        int x = chdir(commandParam);
        if (x)
            printf("Invalid directory name\n");
    }
    else if (strcmp(commandName, "NewFile") == 0 || strcmp(commandName, "NewFile\n") == 0)
    {
        char *commandParam = strtok(NULL, "\n");
        if (commandParam == NULL)
        {
            printf("Please enter a directory path or name\n");
            return;
        }
        int succeed = createFileLocal(commandParam);
        if (succeed == 1)
            printf("Invalid directory path or name\n");
        else if (succeed == 2)
            printf("Directory already created\n");
        else
            printf("Directory successfully created\n");
    }
    else if (strcmp(commandName, "Exit") == 0 || strcmp(commandName, "Exit\n") == 0)
    {
        exitFileExplorer = true;
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
        fgets(command, 100, stdin);
        commandSwitch(command, currPath);
        currPath = currentDirectory();
    }
    return 0;
}