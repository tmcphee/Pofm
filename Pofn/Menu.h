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

		String COMMAND = createString();
		String DISCRIPTION = createString();
		String USAGE = createString();
		int flag = 0;
		char* next = strtok(NULL, "\n");
		if (next == NULL) {
			printf("*****************HELP*****************\n");
			printf("(Use the following commands for targeted help)\n");
			printf("help mv -> Move a file\n");
			printf("help cp -> Copy a file\n");
			printf("help ls -> List files in directitory\n");
			printf("help dir -> Display directitory\n");
			printf("help ndir -> Create a new Directitory\n");
			printf("help cdir -> Change the Directitory\n");
			printf("help nf -> Create a NewFile\n");
			printf("help exit -> Exit the Application\n");
			printf("**************************************\n");
			flag = 1;
		}
		else if (strcmp(next, "mv") == 0) {
			scanString(COMMAND, "mv");
			scanString(DISCRIPTION,  "Move a file from dir x to dir y");
			scanString(USAGE,  "mv SOURCE DESTINATION");
		}
		else if (strcmp(next, "cp") == 0) {
			scanString(COMMAND, "cp");
			scanString(DISCRIPTION,  "Copy a file from dir x to dir y");
			scanString(USAGE,  "mv SOURCE DESTINATION");
		}
		else if (strcmp(next, "ls") == 0) {
			scanString(COMMAND, "ls");
			scanString(DISCRIPTION,  "List all files in the current directitory");
			scanString(USAGE,  "ls");
		}
		else if (strcmp(next, "ndir") == 0) {
			scanString(COMMAND, "ndir");
			scanString(DISCRIPTION,  "Create a new directitory");
			scanString(USAGE,  "ndir DIR_PATH");
		}
		else if (strcmp(next, "cdir") == 0) {
			scanString(COMMAND, "cdir");
			scanString(DISCRIPTION,  "Change the directitory");
			scanString(USAGE,  "cdir DIR_PATH");
		}
		else if (strcmp(next, "nf") == 0) {
			scanString(COMMAND, "nf");
			scanString(DISCRIPTION, "Create a NewFile");
			scanString(USAGE, "nf DIR_PATH");
		}
		else if (strcmp(next, "dir") == 0) {
			scanString(COMMAND, "dir");
			scanString(DISCRIPTION,  "Display the current selected directitory");
			scanString(USAGE,  "dir");
		}
		else {
			printf("Invalid help command\n");
			flag = 1;
		}

		if (flag == 0) {
			printf("*****************HELP*****************\n");
			printf("COMMAND \t%s \n", putString(COMMAND));
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
        fgets(command, 100, stdin);
        commandSwitch(command, currPath);
        currPath = currentDirectory();
    }
    return 0;
}