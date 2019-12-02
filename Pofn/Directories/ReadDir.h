#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

//define maxs
#define MAXFILES 1024
#define MAXPATHLENGTH 255

//gets current directory
char *currentDirectory()
{
    //current working directory
    char cwd[100];
    //returns current working directory
    char *returnCwd = malloc(sizeof(char) * 100);
    //gets cwd
    getcwd(cwd, sizeof(cwd));
    //copies the cwd into return cwd
    strcpy(returnCwd, cwd);
    //returns cwd
    return returnCwd;
}

//checks if directory exists
int directoryExists(const char *path)
{
    //empty directory
    DIR *dir = NULL;
    //changes current directory to path
    chdir(path);
    //opens path
    dir = opendir(path);

    //if exists
    if (dir)
        //return 0
        return 0;
    //else return -1
    else
        return -1;
}

//function to pretty print the current directory
void printDirectory(int folderCounter, char *folders[MAXFILES], char *foldersDateMod[MAXFILES],
                    int fileCounter, char *files[MAXFILES], char *filesDateMod[MAXFILES], _off_t fileSizes[MAXFILES])
{
    //prints titles
    printf("Type\t\t\t\t\tDate last accessed\t\t\tSize\n\n");
    //folders section
    printf("Folders: \n\n");
    //loops through the folders
    for (int i = 0; i < folderCounter; i++)
    {
        //prints the folders
        printf("\t%s", folders[i]);
        printf("\t%s", foldersDateMod[i]);
        printf("\n\n");
        free(folders[i]);
    }
    //files section
    printf("\nFiles: \n\n");
    //prints the files
    for (int i = 0; i < fileCounter; i++)
    {
        //prints the files
        printf("\t%s", files[i]);
        printf("\t%s", filesDateMod[i]);
        printf("\t%ld bytes", fileSizes[i]);
        printf("\n\n");
    }
}

//displays the current directory
int displayDirectory(const char *path)
{
    //empty directory
    DIR *dir = NULL;

    //current dirent pointer
    struct dirent *currDir;
    //fileinfo ptr
    struct stat fileInfo;
    //time info ptr
    struct tm *timeinfo;

    //folder arrays
    char *folders[MAXFILES];
    char *foldersDateMod[MAXFILES];
    char *files[MAXFILES];

    //file arrays
    _off_t fileSizes[MAXFILES];
    char *filesDateMod[MAXFILES];

    //folder counter
    int folderCounter = 0;
    //file counter
    int fileCounter = 0;

    //changes directory to current path
    chdir(path);
    //opens current directory
    dir = opendir(path);

    //if directory does not exist
    if (!dir)
    {
        //error
        fprintf(stderr, "Error: Cannot open the directory\n");
        //return 1
        return 1;
    }

    //loop through everything in the directory
    while ((currDir = readdir(dir)) != NULL)
    {
        //if the file is the /. or the /.. file
        if (!strcmp(currDir->d_name, ".") || !strcmp(currDir->d_name, ".."))
        {
            //ignore it
            continue;
        }

        //get the stats of the current file
        stat(currDir->d_name, &fileInfo);

        //if the file is a directory
        if (S_ISDIR(fileInfo.st_mode))
        {
            //get time info
            timeinfo = localtime(&(fileInfo.st_mtime));
            //allocate memory for date
            foldersDateMod[folderCounter] = (char *)malloc(sizeof(char) * 20);
            //add time to the folders date mod
            strftime(foldersDateMod[folderCounter], 20, "%b %d %H:%M", timeinfo);
            //allocate memory for the folder
            folders[folderCounter] = (char *)malloc(sizeof(char) * MAXPATHLENGTH);
            //add it to the folders array
            strcpy(folders[folderCounter++], (currDir->d_name));
        }
        //if its a file
        else
        {
            //create time info
            timeinfo = localtime(&(fileInfo.st_mtime));
            //allocate memory for the date
            filesDateMod[fileCounter] = (char *)malloc(sizeof(char) * 20);
            //add date to date array
            strftime(filesDateMod[fileCounter], 20, "%b %d %H:%M", timeinfo);
            //allocare memory for the files
            files[fileCounter] = (char *)malloc(sizeof(char) * MAXPATHLENGTH);
            //add file to file array
            strcpy(files[fileCounter], (currDir->d_name));
            //add file size to size array
            fileSizes[fileCounter++] = fileInfo.st_size;
        }
    }

    //print directories
    printDirectory(folderCounter, folders, foldersDateMod, fileCounter, files, filesDateMod, fileSizes);

    //close current directory
    closedir(dir);
    // return
    return 0;
}