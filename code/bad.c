  #include <stdio.h>
  #include <stdlib.h>

  void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
  }

  int main(void) {
      int *a = malloc(3 * sizeof(int));
      a[0] = 1; a[1] = 2; a[2] = 3;

      int x=10;
      int y = 20;

      int *num1 = &x;
      int *num2 = &y;

    //   a[3] = 4;                 // bug 1
    //   printf("%d\n", a[3]);

    swap(num1,num2);


      free(a);
      printf("num1 = %d, num2 = %d \n", *num1,*num2);     // bug 2
      return 0;
  }
