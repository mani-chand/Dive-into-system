#include <stdio.h>
#include <string.h>

struct session {
    char name[8];
    int  is_admin;
};

int main(int argc, char **argv) {
    struct session s = {"", 0};
    snprintf(s.name, sizeof s.name, "%s", argv[1]);      // length check
    printf("name=%s admin=%d\n", s.name, s.is_admin);
    return 0;
}
