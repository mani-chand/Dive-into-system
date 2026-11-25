#include <stdio.h>
#include <string.h>

int main(){
    char a[] = "hello";
    char b[] = "hello";

    printf("size of a %zu\n",sizeof(a));
    printf("strlen of b %zu\n",strlen(b));
    printf("a==b is %d\n",a==b);
    printf("strcmp of a and b is %d\n",strcmp(a,b));
    a[0] = 'j';
    printf("a = %s\n",a);
    char *p = "hello";
    p[0] = 'j';
    return 0;
}