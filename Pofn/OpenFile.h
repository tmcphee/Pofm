#include <stdio.h>
#include <stdlib.h>
#include "liststring.h"

//opens a file
FILE *OpenFileLocal(char *path, char *mode)
{
	//creates a file ptr
	FILE *file = fopen(path, mode);
	//returns file ptr
	return file;
}