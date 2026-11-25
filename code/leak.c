  #include <stdio.h>
  #include <stdlib.h>
  void add_one(int *n) {
      *n = *n + 1;
  }

  int *make_num(void) {
      int *p = malloc(sizeof(int));
      if (p == NULL) return NULL;
      *p = 7;
      return p;
  }



  int main(void) {
    int x = 5;
    add_one(&x);
    printf("%d\n", x);
    int *p = make_num();
    printf("%d\n", *p);
    free(p);

      return 0;
  }
