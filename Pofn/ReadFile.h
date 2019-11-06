#include <stdio.h>
#include <stdlib.h>
#include "liststring.h"

String ReadFile(FILE* file) {
	char c;
	String str = createString();
	while(1){
		if (feof(file)) {
			break;
		}
		c = fgetc(file);
		addChar(str, c);
	}
	return str;
}