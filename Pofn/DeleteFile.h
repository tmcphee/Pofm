#pragma once
#include <stdio.h>
#include "liststring.h"

//two modes, 0 for removing file with global path, or 1 for removing file with local path
int deleteFile(int mode, char *path, char *namec)
{
  //Variables
  int status;		//Stores result of delete
  char *file_name;		//Stores filename
  String str = createString();	//Stores filename in dynamic string
  if (mode == 0)			
  {
    scanString(str, path);
	//For cross platform add different slashes to file path
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

  //If file was not deleted return 1
  if (status != 0)
    return 1;

  //Freeing Memory
  free(file_name);
  freeString(str);
  return 0;
}
