#pragma once
#include <stdio.h>
#include "liststring.h"
#include <dirent.h>

//This function takes a user defined source and destination and either copys or moves a file from the source to the destination

//Mode is 0 for copy, 1 for move (original file is deleted in move)
void moveFileLocal(int mode, char *sourcec, char *destc, char *filenamec)
{
	//Variables
	DIR *source_folder; //actual source and destination DIR pointers
	DIR *destination_folder;
	struct dirent *entry; //The file in question
	char *src, *dest, *n; //c strings for source destination and name
	char ch;
	String source = createString(); //List strings for source destination and name
	String destination = createString();
	String name = createString();
	String buffer = createString(); //the buffer which stores the file while being moved
	String comp1 = createString();  //used to compare equality
	String comp2 = createString();  //used to compare equlaity
	int found = 0;
	long file_length;
	FILE *file;		//file to be moved
	FILE *filedest; //File to be created


	//Scan local variables from inputs
	scanString(source, sourcec);
	scanString(destination, destc);
	scanString(name, filenamec);

	//store user input in proper chars
	src = putString(source);
	dest = putString(destination);
	n = putString(name);

	//If the location being copied to is the same location, copy file instead of moving
	if (stringComp(source, destination))
	{
		copyFileLocal(sourcec, filenamec);
		return;
	};

	//open directorys and check if they exist
	destination_folder = opendir(dest);
	source_folder = opendir(src);

	//If either directory doesn't exist throw error
	if (source_folder == NULL)
	{
		printf("Unable to open Directory %s\n", src);
		perror("The following error occured");
		return;
	}
	else if (destination_folder == NULL)
	{
		printf("Unable to open Directory %s\n", dest);
		perror("The following error occured");
		return;
	}

	//check directory to see if file exist
	while ((entry = readdir(source_folder)) != NULL)
	{
		int i = 0;
		while (i < stringLength(name))
		{
			if (entry->d_name[i] != sgetChar(name, i))
			{
				break; //If the names aren't the same set found to false
			}
			i++;
			if (i == stringLength(name))
			{
				found = 1;	//The name of the file does exist in the target directory
			}
		}
	}

	if (!found)	//If file doesn't exist throw error
	{
		printf("File %s could not be found it either isn't in this folder, or doesn't exist\n", n);
		return;
	}

//Windows uses \ Linux and Mac uses / Make file path based on OS needed for cross platform
#ifdef _WIN32
	addChar(source, (char)(92));
	scanString(source, n);
	addChar(destination, (char)(47));
	scanString(destination, n);
#else
	addChar(source, (char)(92));
	scanString(source, n);
	addChar(destination, (char)(47));
	scanString(destination, n);
#endif

	free(src);
	free(dest);
	src = putString(source);
	dest = putString(destination);

	//Open Files
	file = OpenFileLocal(src, "rb");
	filedest = OpenFileLocal(dest, "wb");

	//Get length of file
	fseek(file, 0, SEEK_END);
	file_length = ftell(file);
	fseek(file, 0, SEEK_SET);

	//copy file
	for (int i = 0; i < file_length; i++)
	{
		ch = fgetc(file);
		fputc(ch, filedest);
	}

	//Closing files
	fclose(filedest);
	fclose(file);

	//delete the original file
	if (mode == 1)
	{
		deleteFile(1, putString(source), " ");
	}

	//freeing memory
	free(destination_folder);
	free(source_folder);
	free(src);
	free(n);
	free(dest);
	freeString(source);
	freeString(name);
	freeString(destination);
}