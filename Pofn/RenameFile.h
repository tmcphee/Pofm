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
	String renames = createString();
	String destination = createString();
	int found = 0, result = 0;
	scanString(source, sourcec);
	scanString(name, old);
	scanString(rename, new);

	n = putString(name);
	filepath = putString(source);
	newname = putString(renames);

	source_folder = opendir(filepath);
	if (source_folder == NULL)
		return 1;

	while ((entry = readdir(source_folder)) != NULL)
	{
		//printf("%s\n", entry->d_name);

		//if (entry->d_name == n) { found = 1; }
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
				found = 1;
			}
		}
	}

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
	addChar(destination, (char)(92));
	scanString(destination, newname);
#endif
	free(filepath);
	filepath = putString(source);
	destpath = putString(destination);
	if (!found)
	{
		return 2;
	}
	result = rename(filepath, destpath);
	if (result != 0)
		return 2;

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