#include <stdio.h>
#include <stdlib.h>
int y = 30;
int main(){
    int x = 10;
    int *ptr = malloc(sizeof(int));
    if(ptr == NULL){
        return 1;
    }
    *ptr = 30;

    printf("Global: %d\n", y);
    printf("Local: %d\n", x);
    printf("Heap: %d\n", *ptr);
    free(ptr);
    return 0;
}