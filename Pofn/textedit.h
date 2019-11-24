#pragma once

/*Append text to the end of a file Insert text in a specific position(counted in characters) of the file, 
Remove all text in a file, Show the content of a text file, with the ability to pause per page.The number
of lines per page can be specified by the user.*/
//To use pass a choice input by user in start menu
void editText(char choice) {
	DIR* source_folder;		//actual source and destination DIR pointers
	FILE* txt;
	String file_path = createString();	//file path string
	String file_name = createString();
	String file;
	String append = createString();
	char *fpath, *name;	//file path c string
	char action = 'C';
	char ch;
	int index = 0, numlines;

	printf("Enter the folder of the file you wish to open: ");
	stringGets(file_path);
	fpath = putString(file_path);
	source_folder = opendir(fpath);
	if (source_folder == NULL) {
		printf("Unable to open Directory %s\n", fpath);
		perror("The following error occured");
		return;
	}

	printf("Enter the name of the text file you wish to open: ");
	stringGets(file_name);
	name = putString(file_name);

	#ifdef _WIN32
		addChar(file_path, (char)(92));
		scanString(file_path, name);
	#else
		addChar(file_path, (char)(92));
		scanString(file_path, name);
	#endif
	free(name);
	name = putString(file_path);

	switch (choice) {
		case('O')://read a files conents line by line
			txt = fopen(name, "r+");
			if (txt == NULL) {
				printf("File %s does not exist.", name);
				return;
			}
			file = ReadFileLocal(txt);

			printf("Enter the number of lines per page: ");
			scanf("%d", &numlines);
			
			while (1) {
				for (int i = 0; i < numlines; i++) {
					while (sgetChar(file, index) != '\n' && index < stringLength(file)) {
						printf("%c", (sgetChar(file, index)));
						index++;
					}
					printf("\n");
					index++;
					if (index == stringLength(file)) {
						break;
					}
				}
				if (index == stringLength(file)) {
					printf("end of file reached");
					break;
				}
			
				printf("Enter a choice [C] to continue [Q] to quit: ");
				fflush(stdin);
				action = getchar();
				if (action == 'Q') {
					break;
				}
			}
			fclose(txt);
			free(file);
			break;

		case('D')://Remove all text from a file
			txt = fopen(name, "w");
			fprintf(txt, "");
			fclose(txt);
			break;

		case('I')://Insert text to a certain position in a file
			txt = fopen(name, "r+");
			if (txt == NULL) {
				printf("File %s does not exist.", name);
				return;
			}
			file = ReadFileLocal(txt);
			printf("Enter the position you wish to insert the text at: ");
			scanf("%d", &index);
			if (!(index < stringLength(file) && index >= 0)) { printf("Invalid index entered"); return; };
			printf("Enter the text you wish to append to the file, press enter to submit: ");
			stringGets(append);

			for (int i = 0; i < stringLength(append); i++) {
				if (i % 150 == 0 && i != 0) {
					addCharIndex(file, '\n', index);
				}
				ch = sgetChar(append, i);
				addCharIndex(file, ch, index);
			}

			for (int i = 0; i < stringLength(file); i++) {
				ch = sgetChar(file, i);
				fputc(ch, txt);
			}
			free(file);
			break;

		case('A')://Append text to the end of a text document
			txt = fopen(name, "r+");
			if (txt == NULL) {
				printf("File %s does not exist.", name);
				return;
			}
			file = ReadFileLocal(txt);
			printf("Enter the text you wish to append to the file, press enter to submit: \n");
			stringGets(append);

			for (int i = 0; i < stringLength(append); i++) {
				if (i % 150 == 0 && i != 0) {
					addChar(file, '\n');
				}
				ch = sgetChar(append, i);
				addChar(file, ch);
			}

			for (int i = 0; i < stringLength(file); i++) {
				ch = sgetChar(file, i);
				fputc(ch, txt);
			}
			free(file);
			break;
	}
	freeString(file_path);
	return;
}