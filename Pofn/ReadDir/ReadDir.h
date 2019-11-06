#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

#define MAXFILES 1024

int displayDirectory(const char *path)
{

    DIR *dir = NULL;
    struct dirent *currDir;
    struct stat fileInfo;
    struct tm *timeinfo;
    char *folders[MAXFILES];
    char *foldersDateMod[MAXFILES];
    char *files[MAXFILES];
    _off_t fileSizes[MAXFILES];
    char *filesDateMod[MAXFILES];
    int folderCounter = 0;
    int fileCounter = 0;

    chdir(path);
    dir = opendir(path);

    if (!dir)
    {
        fprintf(stderr, "Error: Cannot open the directory\n");
        return 1;
    }

    while ((currDir = readdir(dir)) != NULL)
    {
        if (!strcmp(currDir->d_name, ".") || !strcmp(currDir->d_name, ".."))
        {
            continue;
        }

        stat(currDir->d_name, &fileInfo);

        if (S_ISDIR(fileInfo.st_mode))
        {
            timeinfo = localtime(&(fileInfo.st_mtime));
            foldersDateMod[folderCounter] = malloc(sizeof(char) * 20);
            strftime(foldersDateMod[folderCounter], 20, "%b %d %H:%M", timeinfo);
            folders[folderCounter] = malloc(sizeof(char) * 260);
            strcpy(folders[folderCounter++], (currDir->d_name));
        }
        else
        {
            timeinfo = localtime(&(fileInfo.st_mtime));
            filesDateMod[fileCounter] = malloc(sizeof(char) * 20);
            strftime(filesDateMod[fileCounter], 20, "%b %d %H:%M", timeinfo);
            files[fileCounter] = malloc(sizeof(char) * 260);
            strcpy(files[fileCounter], (currDir->d_name));
            fileSizes[fileCounter++] = fileInfo.st_size;
        }
    }

    printf("Type\t\t\t\t\tDate last accessed\t\t\tSize\n\n");
    printf("Folders: \n");
    for (int i = 0; i < folderCounter; i++)
    {
        printf("\t%s", folders[i]);
        printf("\t%s", foldersDateMod[i]);
        printf("\n\n");
        free(folders[i]);
    }
    printf("\nFiles: \n");
    for (int i = 0; i < fileCounter; i++)
    {
        printf("\t%s", files[i]);
        printf("\t%s", filesDateMod[i]);
        printf("\t%ld bytes", fileSizes[i]);
        printf("\n\n");
    }

    closedir(dir);
    return 0;
}