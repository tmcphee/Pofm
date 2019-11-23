#include <stdio.h>
#include <stdlib.h>
#include "liststring.h"

FILE* OpenFileLocal(char* path, char* mode) {
	FILE* file = fopen(path, mode);
	return file;
}