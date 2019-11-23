#pragma once


void createFileLocal() {
	DIR* source_folder; //where the file should be created
	char *fpath, *buff, *foldpath;
	char ch;
	String filename = createString();
	String filepath = createString();
	String userinput = createString();
	FILE* userfile;

	printf("Enter the folder which you would like to create the file in: ");
	stringGets(filepath);
	foldpath = putString(filepath);
	source_folder = opendir(foldpath);

	if (source_folder == NULL) {
		printf("Unable to open Directory %s\n", foldpath);
		perror("The following error occured: ");
		closedir(source_folder);
		free(foldpath);
		return;
	}
	free(foldpath);

	closedir(source_folder);
	printf("What should the name of the file be: ");
	stringGets(filename);

	#ifdef _WIN32
		addChar(filepath, (char)(92));
	#else
		addChar(filepath, (char)(92));
	#endif

	stringCat(filepath, filename);
	fpath = putString(filepath);
	userfile = OpenFileLocal(fpath, "w");
	printf("Continue to enter text until you are done, hit enter to submit text: \n");
	stringGets(userinput);
	buff = putString(userinput);

	for (int i = 0; i < stringLength(userinput); i++) {
		if (i % 150 == 0 && i != 0) {
			fprintf(userfile, "\n");
		}
		ch = buff[i];
		fputc(ch, userfile);
	}
	fclose(userfile);
	free(fpath);
	free(buff);
	freeString(filename);
	freeString(filepath);
	freeString(userinput);
}