#pragma once

/*Append text to the end of a file Insert text in a specific position(counted in characters) of the file, 
Remove all text in a file, Show the content of a text file, with the ability to pause per page.The number
of lines per page can be specified by the user.*/
//To use pass a choice input by user in start menu
int editText(char *source, char *fname)
{
	fflush(stdin);
	DIR *source_folder; //actual source and destination DIR pointers
	FILE *txt;
	String file_path = createString(); //file path string
	String file_name = createString();
	String file;
	String append = createString();
	char *fpath, *name; //file path c string
	char action = 'C';
	char ch, choice;
	int index = 0, numlines;

	//Get user input for operation choice
	printf("Enter the operation you would like to perform \n");
	printf("O- read file \nD- remove all text from file \nI- insert text at position \nA- append text\nChoice:  ");
	scanf("%c", &choice);
	getchar();
	choice = toupper(choice);

	//Store local variables
	scanString(file_path, source);
	fpath = putString(file_path);

	
	source_folder = opendir(fpath);	//Attempt to open directory
	if (source_folder == NULL)		//if directory does not exist return error
	{
		return 1;
	}

	//Set local variables
	scanString(file_name, fname);
	deleteCharValue(file_name, '\n');
	name = putString(file_name);

	//OS specific code, uses \ for windows and / for every other OS
#ifdef _WIN32
	addChar(file_path, (char)(92));
	scanString(file_path, name);
#else
	addChar(file_path, (char)(47));
	scanString(file_path, name);
#endif
	//Update path to include name of file
	free(name);
	name = putString(file_path);

	//Switch statement for different choices
	switch (choice)
	{
	case ('O'): //read a files conents line by line
		txt = fopen(name, "r+");	//open file in read mode
		if (txt == NULL)	//If file does not exist free variables and return error
		{
			freeString(file_path);
			freeString(file_name);
			free(name);
			free(fpath);
			return 2;
		}
		file = ReadFileLocal(txt);	//otherwise open the file

		printf("Enter the number of lines per page: ");
		scanf("%d", &numlines);	//get number of lines per page from user

		while (1)	//While true
		{
			for (int i = 0; i < numlines; i++)	//for the number of lines specified by user
			{
				while (sgetChar(file, index) != '\n' && index < stringLength(file))	//go until new line
				{
					printf("%c", (sgetChar(file, index)));	//Print the character
					index++;
				}
				printf("\n");	//Print new line
				index++;
				if (index == stringLength(file))	//If end of text file, exit
				{
					break;
				}
			}
			if (index == stringLength(file))
			{
				printf("end of file reached");
				break;
			}

			printf("Enter a choice [C] to continue [Q] to quit: ");	//Let user decide to continu or quit
			getchar();
			action = getchar();
			action = toupper(action);

			if (action == 'Q')	//If user wishes to exit beak
			{
				break;
			}
		}
		fclose(txt);
		free(file);
		break;

	case ('D'): //Remove all text from a file
		txt = fopen(name, "w");	//Open file
		fprintf(txt, "");		//Print empty string
		fclose(txt);			//Close text file
		break;

	case ('I'): //Insert text to a certain position in a file
		txt = fopen(name, "r+");	//Open file in read mode with ability to write
		if (txt == NULL)		//If file does not exist throw error
		{
			printf("File %s does not exist.", name);
			freeString(file_path);
			freeString(file_name);
			free(name);
			free(fpath);
			return 2;
		}

		file = ReadFileLocal(txt);	//read file contents
		fclose(txt);
		txt = fopen(name, "w");	//open file for writing
		printf("Enter the position you wish to insert the text at: ");	
		scanf("%d", &index);	//get index to insert text from user
		if (!(index < stringLength(file) && index >= 0))	//if the index is bigger than the text file or smaller than 0 return error
		{
			return 3;
		};
		printf("Enter the text you wish to append to the file, press enter to submit: ");
		getchar();
		stringGets(append);	//get text to add to file

		for (int i = 0; i < stringLength(append); i++)	//loop through whole string
		{
			if (i % 150 == 0 && i != 0)	//Every 150 characters print a new line
			{
				addCharIndex(file, '\n', index + i);
			}
			ch = sgetChar(append, i);	
			addCharIndex(file, ch, index + i); //add character to file String at index
		}

		//Loop through whole file String and print characters
		for (int i = 0; i < stringLength(file) - 1; i++)
		{
			ch = sgetChar(file, i);	
			fputc(ch, txt);
		}
		free(file);
		fclose(txt);
		break;

	case ('A'): //Append text to the end of a text document
		txt = fopen(name, "r+");	//Open in read mode
		if (txt == NULL)	//if file does not exist return error
		{
			freeString(file_path);
			freeString(file_name);
			free(name);
			free(fpath);
			return 2;
		}

		file = ReadFileLocal(txt); //read file contents
		printf("Enter the text you wish to append to the file, press enter to submit: \n");	//Get text to append
		stringGets(append);

		//Loop through string and append text
		for (int i = 0; i < stringLength(append); i++)
		{
			ch = sgetChar(append, i);
			fputc(ch, txt);
		}
		free(file);
		fclose(txt);
		break;
	}
	freeString(file_path);
	freeString(file_name);
	free(name);
	free(fpath);
	return 0;
}