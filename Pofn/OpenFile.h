#include <stdio.h>
#include <stdlib.h>
#include "liststring.h"

FILE* OpenFile(char* path) {
	FILE* file = fopen(path, "a+");
	return file;
}