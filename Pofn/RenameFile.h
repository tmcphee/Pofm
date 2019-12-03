#pragma once
#include <stdio.h>

//finish rename
int renameLocal(char *sourcec, char *old, char *new)
{
	DIR *source_folder;
	struct dirent *entry;					 //The file in question
	char *newname, *n, *filepath, *destpath; //char pointers to store file name, directory name, and full path to file
	String name = createString();			 //name of file
	String source = createString();			 //name of source directory
	String renames = createString();		 //new name
	String destination = createString();	 //destination
	int found = 0, result = 0;				 //variables for while loops

	//Set strings to match inputs
	scanString(source, sourcec);			 
	scanString(name, old);
	scanString(renames, new);

	//Set local variables to match inputs
	n = putString(name);
	filepath = putString(source);
	newname = putString(renames);

	
	source_folder = opendir(filepath);	//Set directory folder
	if (source_folder == NULL)		//If directory does not exist throw error
		return 1;

	while ((entry = readdir(source_folder)) != NULL)	//While there are still files in source directory
	{
		//Loop variable
		int i = 0;
		while (i < stringLength(name))	//Loop through string
		{
			if (entry->d_name[i] != sgetChar(name, i))	//check if characters at position i in names are the same
			{
				break; //If the names aren't the same set found to false
			}
			i++;
			if (i == stringLength(name))
			{
				found = 1;	//File does exist
			}
		}
	}


	//Cross platform code, on windows use \ on other os' use / 
#ifdef _WIN32
	addChar(source, (char)(92));
	stringCopy(destination, source);
	scanString(source, n);
	addChar(destination, (char)(92));
	scanString(destination, newname);
#else
	addChar(source, (char)(47));
	stringCopy(destination, source);
	scanString(source, n);
	addChar(destination, (char)(47));
	scanString(destination, newname);
#endif
	
	free(filepath);	//clears the string

	filepath = putString(source);		//new filepath with os specific name
	destpath = putString(destination);  //new destination path with os specific name

	if (!found) //If the file that was supposed to be renamed doesn't exist, throw an error
	{
		return 2;
	}

	//attemept to rename, if fails return error
	result = rename(filepath, destpath);
	if (result != 0)
		return 2;

	//free variables
	free(destpath);
	free(filepath);
	free(n);
	free(newname);
	freeString(name);
	freeString(source);
	freeString(destination);
	freeString(renames);
	return 0;
}