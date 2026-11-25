  #include <stdio.h>

  int main(void) {
      int *num = 10;
      printf("%p\n", (void *)num);   // prints the address
      printf("%d\n", *num);          // reads from address 10
      return 0;
  }
