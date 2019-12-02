#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "ReadDir.h"
#include <string.h>

//gets the parent directory
const char *parentDirectory(const char *path)
{
    //variable to temporarily hold path info
    char *tempPath = _strdup(path);
    //breaks up the path by /
    char *token = strtok(tempPath, "/");
    //creates memrory to hold new path
    char *newPath = (char *)malloc(sizeof(char) * MAXPATHLENGTH);
    //clears the memory
    memset(newPath, '\0', MAXPATHLENGTH);
    //creates a temp
    char *temp = (char *)malloc(sizeof(char) * MAXPATHLENGTH);
    //sets temp equal to nothing
    temp = "";
    //while theres still stuff after the slash
    while (token != NULL)
    {
        //temp = the token
        temp = _strdup(token);
        //get the next section after a /
        token = strtok(NULL, "/");
        //if the token is not null
        if (token != NULL)
        {
            //concatenate the newpath and temp
            newPath = strcat(newPath, temp);
            //add an ending /
            newPath = strcat(newPath, "/");
        }
    }
    //create a constchar to the new path
    const char *constNewPath = _strdup(newPath);
    //free all memory
    free(newPath);
    free(temp);
    //return new path
    return constNewPath;
}

//creates directory
int createDirectory(const char *path)
{

    //if directory already exists return 2
    if (!directoryExists(path))
        return 2;

    //mkdir path
    int mkDirAttempt = mkdir(path);
    //if unsuccessful
    if (mkDirAttempt)
    {
        //get parent directory
        const char *newPath = parentDirectory(path);
        //create parent directory
        createDirectory(newPath);
        //create current path
        createDirectory(path);
    }
    //return success
    return 0;
}