#include <stdio.h>
#include <stdlib.h>
#include "liststring.h"

String ReadFile(FILE* file, char* output) {
	char c;
	String str = createString();
	while(true){
		if (feof(file)) {
			break;
		}
		c = fgetc(file);
		addChar(str, c);
	}
	return str;
}