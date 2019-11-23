#pragma once
#include <stdio.h>

//finish rename
void renameLocal() {
	DIR* source_folder;
	struct dirent* entry;	//The file in question
	char *newname, *n, *filepath, *destpath;	//char pointers to store file name, directory name, and full path to file
	String name = createString();	//name of file
	String source = createString();	//name of source directory
	String renames = createString();
	String destination = createString();
	int found = 0, result = 0;
	printf("Enter the directory of the file: ");
	stringGets(source);
	printf("Enter the name of the file: ");
	stringGets(name);
	printf("Enter the new name of the file: ");
	stringGets(renames);

	n = putString(name);
	filepath = putString(source);
	newname = putString(renames);

	source_folder = opendir(filepath);
	if (source_folder == NULL) {
		printf("Unable to open Directory %s\n", filepath);
		perror("The following error occured");
		return;
	}

	while ((entry = readdir(source_folder)) != NULL) {
		//printf("%s\n", entry->d_name);

		//if (entry->d_name == n) { found = 1; }
		int i = 0;
		while (i < stringLength(name)) {
			if (entry->d_name[i] != sgetChar(name, i)) {
				break;	//If the names aren't the same set found to false
			}
			i++;
			if (i == stringLength(name)) { 
				found = 1;
			}
		}
	}

	#ifdef _WIN32
		addChar(source, (char)(92));
		stringCopy(destination, source);
		scanString(source, n);
		scanString(destination, newname);
	#else
		addChar(source, (char)(92));
		scanString(source, n);
		stringCopy(destination, source);
		scanString(destination, "-Copy");
	#endif
		free(filepath);
		filepath = putString(source);
		destpath = putString(destination);
	if (!found) {
		printf("File %s could not be found it either isn't in this folder, or doesn't exist", n);
		return;
	}
	result = rename(filepath, destpath);
	if (result == 0)
		printf("File successfully renamed");
	else
		perror("Error renaming file");

	free(destpath);
	free(filepath);
	free(n);
	free(newname);
	freeString(name);
	freeString(source);
	freeString(destination);
	freeString(renames);
}