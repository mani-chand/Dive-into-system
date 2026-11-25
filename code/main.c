 #include <stdio.h>

   int is_even(int n) {
      // your code: return 1 if even, 0 if odd
      return n % 2 == 0;
    }


  int sum_to(int n) {
      int sum = 0;
      for (int i = 1; i <= n; i++) {
          sum = sum + i;
      }
      return sum;
  }

  int main(void) {
      printf("sum to 10  = %d\n", sum_to(10));
      printf("sum to 100 = %d\n", sum_to(100));
      printf("8 -> %d\n", is_even(8));
      printf("15 -> %d\n", is_even(15));


      return 0;
  }
