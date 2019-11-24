
//fix file extension, instead of testfile.png -> testfile.png-copy | testfile.png -> testfile-copy.png

void copyFileLocal() {
	//Variables
	DIR* source_folder;		//actual source and destination DIR pointers
	struct dirent* entry;	//The file in question
	char* src, * n, *dest;	//c strings for source destination and name
	char ch;
	String source = createString();		//List strings for source destination and name
	String name = createString();
	String buffer = createString(); //the buffer which stores the file while being moved
	String comp1 = createString();	//used to compare equality
	String comp2 = createString();	//used to compare equlaity
	String destination = createString();
	int found = 0;
	long file_length;
	FILE* file; //file to be moved
	FILE* filedest;//File to be created

	//dir = opendir(".");
	//Get user input need : name of file ex. c/users/jack/filename.png	folder to move file to ex. c/users/jack/newfolder new filename
	printf("Enter the source folder of the file you wish to copy: ");
	stringGets(source);
	printf("Enter the Name of the file: ");
	stringGets(name);

	//store user input in proper chars
	src = putString(source);
	n = putString(name);

	//open directorys and check if they exist
	source_folder = opendir(src);
	if (source_folder == NULL) {
		printf("Unable to open Directory %s\n", src);
		perror("The following error occured");
		return;
	}

	//check directory to see if file exist
	while ((entry = readdir(source_folder)) != NULL) {
		//printf("%s\n", entry->d_name);

		//if (entry->d_name == n) { found = 1; }
		int i = 0;
		while (i < stringLength(name)) {
			if (entry->d_name[i] != sgetChar(name, i)) {
				break;	//If the names aren't the same set found to false
			}
			i++;
			if (i == stringLength(name)) { found = 1; }
		}
	}

	if (!found) {
		printf("File %s could not be found it either isn't in this folder, or doesn't exist", n);
		return;
	}

	//Windows uses \ Linux and Mac uses / Make file path based on OS needed for cross platform
#ifdef _WIN32
	addChar(source, (char)(92));
	scanString(source, n);
	stringCopy(destination, source);
	scanString(destination, "-Copy");
#else
	addChar(source, (char)(92));
	scanString(source, n);
	stringCopy(destination, source);
	scanString(destination, "-Copy");
#endif

	free(src);
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
	for (int i = 0; i < file_length; i++) {
		ch = fgetc(file);
		fputc(ch, filedest);
	}

	//Closing files
	fclose(filedest);
	fclose(file);

	//freeing memory
	free(source_folder);
	free(src);
	free(n);
	free(dest);
	freeString(source);
	freeString(name);
	freeString(destination);
}