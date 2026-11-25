#include <stdio.h>

#define ROW 2
#define COL 3

int main(){
    int g[ROW][COL] =  { {1, 2, 3}, {4, 5, 6} };
    int sum = 0;
    for(int r = 0; r < ROW; r++){
        for(int c = 0; c < COL; c++){
            printf("g[%d][%d] = %d\n", r, c, g[r][c]);
            sum += g[r][c];
        }   
    }
    printf("sum = %d\n", sum);
    printf("%d\n", *(&g[0][0] + 4));
    printf("%d\n", g[1][5]);
    return 0;
}