#include "ReadDir.h"
#include <stdlib.h>

int main()
{
    displayDirectory(".");
    displayDirectory("C:/Users/Connor/Documents/GitHub/Pofm/Pofn");
    printf("%s", currentDirectory());
}