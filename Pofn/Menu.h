#include "Directories/MakeDir.h"
#include <stdbool.h>

bool exitFileExplorer = false;

void commandSwitch(char command[100], char *path)
{
    char *commandName = strtok(command, " ");

    if (strcmp(commandName, "dir") == 0 || strcmp(commandName, "dir\n") == 0)
    {
        displayDirectory(path);
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
    else if (strcmp(commandName, "cdir") == 0 || strcmp(commandName, "cdir\n") == 0)
    {
        char *commandParam = strtok(NULL, "\n");
        int x = chdir(commandParam);
        if (x)
            printf("Invalid directory name\n");
    }
    else if (strcmp(commandName, "nf") == 0 || strcmp(commandName, "nf\n") == 0)
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
    else if (strcmp(commandName, "exit") == 0 || strcmp(commandName, "exit\n") == 0)
    {
        exitFileExplorer = true;
    }
	else if (strcmp(commandName, "help") == 0 || strcmp(commandName, "help\n") == 0)
	{
		if (strcmp(commandName, "help\n") == 0) {
			printf("HELP (Use the following commands for targeted help)\n\n");
			printf("help mv -> Move a file\n");
			printf("help cp -> Copy a file\n");
			printf("help ls -> List files in directitory\n");
			printf("help dir -> Display directitory\n");
			printf("help ndir -> Create a new Directitory\n");
			printf("help cdir -> Change the Directitory\n");
			printf("help nf -> Create a NewFile\n");
			printf("help exit -> Exit the Application\n");
		}
		else if (strcmp(commandName, "help mv\n") == 0) {
			printf("COMMAND *mv* HELP\n");
			printf("DISCRIPTION: Move a file from dir x to dir y\n");
			printf("USAGE: *mv SOURCE DESTINATION*\n");
		}
		else if (strcmp(commandName, "help cp\n") == 0) {
			printf("COMMAND *cp* HELP\n");
			printf("DISCRIPTION: Move a file from dir x to dir y\n");
			printf("USAGE: *mv SOURCE DESTINATION*\n");
		}
		else if (strcmp(commandName, "help ls\n") == 0) {
			printf("COMMAND *ls* HELP\n");
			printf("DISCRIPTION: List all files in the current directitory\n");
			printf("USAGE: *ls*\n");
		}
		else if (strcmp(commandName, "help ndir\n") == 0) {
			printf("COMMAND *ndir* HELP\n");
			printf("DISCRIPTION: Create a new directitory\n");
			printf("USAGE: *ndir DIR_PATH*\n");
		}
		else if (strcmp(commandName, "help cdir\n") == 0) {
			printf("COMMAND *cdir* HELP\n");
			printf("DISCRIPTION: Change the directitory\n");
			printf("USAGE: *cdir DIR_PATH*\n");
		}
		else if (strcmp(commandName, "help nf\n") == 0) {
			printf("COMMAND *nf* HELP\n");
			printf("DISCRIPTION: Create a NewFile\n");
			printf("USAGE: *nf DIR_PATH*\n");
		}
		else if (strcmp(commandName, "help dir\n") == 0) {
			printf("COMMAND *dir* HELP\n");
			printf("DISCRIPTION: Display the current selected directitory\n");
			printf("USAGE: *dir*\n");
		}
		else {
			printf("Invalid help command/n");
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
        fgets(command, 100, stdin);
        commandSwitch(command, currPath);
        currPath = currentDirectory();
    }
    return 0;
}