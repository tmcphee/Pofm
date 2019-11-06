#include <stdio.h>
#include <stdlib.h>
#include "liststring.h"
#include "OpenFile.h"
#include "ReadFile.h"

int main() {
	FILE* file = OpenFile("text.txt");
	String str = ReadFile(file);
	printString(str);
}