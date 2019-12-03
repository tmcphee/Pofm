#include <stdio.h>
#include <stdlib.h>
#include "liststring.h"

//reads a local file
String ReadFileLocal(FILE *file)
{
	//declares variable to hold a single char
	char c;
	//creates a string
	String str = createString();
	//infinite loop
	while (1)
	{
		//if end of file
		if (feof(file))
		{
			//break
			break;
		}
		//else get the next character in file
		c = fgetc(file);
		//add the character to the string
		addChar(str, c);
	}
	//return the string
	return str;
}