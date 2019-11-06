#include <stdio.h>
#include <stdlib.h>
#include "liststring.h"

FILE* OpenFile(String path) {
	FILE* file = fopen(path, "w+");
	return file;
}