  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h> 
  #include <time.h>
    // returns 1 on success, 0 on bad input, -1 on end of input
  int read_int(int *out) {
      char line[16];
      if (fgets(line, sizeof line, stdin) == NULL) {
          return -1;
      }
      if (strchr(line, '\n') == NULL) {      // line was too long
          int c;
          while ((c = getchar()) != '\n' && c != EOF) {
              // discard the rest of this line
          }
          return 0;
      }
      char *end;
      long v = strtol(line, &end, 10);
      if (end == line || *end != '\n') {     // no digits, or junk after them
          return 0;
      }
      if (v < -1000000 || v > 1000000) {     // keep it small, avoids int overflow
          return 0;
      }
      *out = (int)v;
      return 1;
  }


  int main(void) {
    srand(time(NULL));
    int secret = rand() % 100 + 1;

      char line[16];

      for (int tries = 1; tries <= 5; tries++) {
          printf("guess %d/5: ", tries);
          int g;
          int r = read_int(&g);
          if (r == -1) return 1;
          if (r == 0) { printf("enter a number\n"); tries--; continue; }
          if (g == secret) { 
              printf("correct in %d tries\n", tries);
              return 0;
          } else if (g < secret) {
              printf("too low\n");
          } else {
              printf("too high\n");
          }
      }
      printf("out of tries, it was %d\n", secret);
      return 0;
  }
