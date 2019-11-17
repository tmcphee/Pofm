#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "ReadDir.h"
#include <string.h>

const char *parentDirectory(const char *path)
{
    char *tempPath = strdup(path);
    char *token = strtok(tempPath, "/");
    char *newPath = (char *)malloc(sizeof(char) * MAXPATHLENGTH);
    char *temp = (char *)malloc(sizeof(char) * MAXPATHLENGTH);
    temp = "";
    while (token != NULL)
    {
        temp = strdup(token);
        token = strtok(NULL, "/");
        if (token != NULL)
        {
            newPath = strcat(newPath, temp);
            newPath = strcat(newPath, "/");
        }
    }
    const char *constNewPath = strdup(newPath);
    free(newPath);
    free(temp);
    return constNewPath;
}

int createDirectory(const char *path)
{
    if (!directoryExists(path))
    {
        printf("Directory already exists");
        return 0;
    }

    int mkDirAttempt = mkdir(path);
    if (!mkDirAttempt)
        printf("File successfully created :D\n");
    else
    {
        const char *newPath = parentDirectory(path);
        createDirectory(newPath);
        createDirectory(path);
    }
}