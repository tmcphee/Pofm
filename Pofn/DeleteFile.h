#include <stdio.h>

int main()
{
  int status;
  char file_name[50];

  printf("Enter name of a file you wish to delete: ");
  scanf("%s", file_name);

  status = remove(file_name);

  if (status == 0)
    printf("%s file deleted successfully.\n", file_name);
  else
  {
    printf("Unable to delete the file\n");
    perror("The following error occurred");
  }

}
