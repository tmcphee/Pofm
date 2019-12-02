#pragma once

int createFileLocal(char *sourcec, char *namec)
{
	DIR *source_folder; //where the file should be created
	char *fpath, *buff, *foldpath; //char pointers to store locations
	char ch;    //temp variable, just used for assigning input to file
	String filename = createString();
	String filepath = createString();
	String userinput = createString();
	FILE *userfile;    //file to be created

	scanString(filepath, sourcec);      //store source folder
	foldpath = putString(filepath);     //store source folder
	source_folder = opendir(foldpath);  //open source directory

	if (source_folder == NULL)  //if folder does not exist return error
	{
		printf("Unable to open Directory %s\n", foldpath);
		perror("The following error occured: ");
		closedir(source_folder);
		free(foldpath);
		return 1;
	}
	free(foldpath);

	closedir(source_folder);
	scanString(filename, namec); // load name of file

#ifdef _WIN32    //If on windows add forward slash to path otherwise add backslash, need for cross platform
	addChar(filepath, (char)(92)); 
#else
	addChar(filepath, (char)(47));
#endif
        //store full file path including filename
	stringCat(filepath, filename);
	fpath = putString(filepath);
        
        //Make sure filename has a txt extension
	char txt[5] = "txt.";
	for (int i = 0; i < 4; i++)
	{
		if (sgetChar(filename, stringLength(filename) - (i + 1)) != txt[i])
		{
			return 2;
		};
	}
      
        //open file and write user input to file
	userfile = OpenFileLocal(fpath, "w");
	printf("Continue to enter text until you are done, hit enter to submit text: \n");
	stringGets(userinput);
	buff = putString(userinput);

	for (int i = 0; i < stringLength(userinput); i++)
	{
		if (i % 150 == 0 && i != 0)
		{
			fprintf(userfile, "\n");
		}
		ch = buff[i];
		fputc(ch, userfile);
	}
   
        //close file and free memory
	fclose(userfile);
	free(fpath);
	free(buff);
	freeString(filename);
	freeString(filepath);
	freeString(userinput);
	return 0;
}
