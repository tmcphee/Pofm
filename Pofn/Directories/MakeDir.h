#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "ReadDir.h"
#include <string.h>

const char *parentDirectory(const char *path)
{
    char *tempPath = _strdup(path);
    char *token = strtok(tempPath, "/");
    char *newPath = (char *)malloc(sizeof(char) * MAXPATHLENGTH);
    memset(newPath, '\0', MAXPATHLENGTH);
    char *temp = (char *)malloc(sizeof(char) * MAXPATHLENGTH);
    temp = "";
    while (token != NULL)
    {
        temp = _strdup(token);
        token = strtok(NULL, "/");
        if (token != NULL)
        {
            newPath = strcat(newPath, temp);
            newPath = strcat(newPath, "/");
        }
    }
    const char *constNewPath = _strdup(newPath);
    free(newPath);
    free(temp);
    return constNewPath;
}

int createDirectory(const char *path)
{

    if (!directoryExists(path))
        return 2;

    int mkDirAttempt = mkdir(path);
    if (mkDirAttempt)
    {
        const char *newPath = parentDirectory(path);
        createDirectory(newPath);
        createDirectory(path);
    }
    return 0;
}