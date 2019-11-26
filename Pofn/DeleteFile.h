#pragma once
#include <stdio.h>
#include "liststring.h"

int deleteFile(int mode, char *path, char *namec)
{
  //Variables
  int status;
  char *file_name;
  String str = createString();
  if (mode == 0)
  {
    scanString(str, path);
#ifdef _WIN32
    addChar(str, (char)(92));
#else
    addChar(str, (char)(47));
#endif
    scanString(str, namec);
    file_name = putString(str);
  }
  else
  {
    file_name = path;
  }

  status = remove(file_name); //Attempt to remove the file if it exist, otherwise throw error

  if (status != 0)
    return 1;

  //Freeing Memory
  free(file_name);
  freeString(str);
  return 0;
}
