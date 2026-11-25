  #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>
  char *copy_name(const char *src) {
      // allocate strlen(src) + 1, check NULL, copy, return
      char *temp = malloc(strlen(src) + 1);
      if(temp == NULL){
        return NULL;
      }
      strcpy(temp,src);
      return temp;
  }

  int main(void) {
      char *n = copy_name("Mani");
      // check n, print, free
      if(n == NULL){
        printf("Not able allocate Memory\n");
        return 1;
      }
      printf("n = %s\n",n);
      free(n);
      return 0;
  }
