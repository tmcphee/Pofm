#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "liststring.h"
#include "OpenFile.h"
#include "ReadFile.h"
#include "MoveFile.h"
#include "CopyFile.h"
#include "DeleteFile.h"
#include "RenameFile.h"
#include "CreateFile.h"

int main(int argc, char* argv[]) {
	/*if (argc == 0) {
		menu();
	}
	FILE* file = OpenFile("text.txt");
	String str = ReadFile(file);
	printString(str);*/
	
	//moveFileLocal(1);
	copyFileLocal();
	//renameLocal();
	//createFileLocal();
}