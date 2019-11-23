#pragma once
#include <stdio.h>
#include "liststring.h"


int deleteFile(int mode, char* path)
{
  //Variables
  int status;
  char* file_name;
  String str = createString();
  if (mode == 0) {
	 printf("Enter name of a file you wish to delete: ");
	 //Store filename in a string, then point to char array
	 stringGets(str);
	 file_name = putString(str);
  }
  else {
	  file_name = path;
  }

  status = remove(file_name);	//Attempt to remove the file if it exist, otherwise throw error

  if (status == 0 && mode == 0)
    printf("%s file deleted successfully.\n", file_name);
  else if(mode == 0)
  {
    printf("Unable to delete the file\n");
    perror("The following error occurred");
  }

  //Freeing Memory
  free(file_name);
  freeString(str);
  return 1;
}
