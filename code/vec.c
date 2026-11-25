#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;      // heap array
    size_t len;     // items used
    size_t cap;     // slots allocated
} Vec;

int  vec_init(Vec *v);                 // allocate cap=4. return 0 ok, -1 fail
int  vec_push(Vec *v, int x);          // add; grow if len == cap
int  vec_get(const Vec *v, size_t i, int *out); // bounds-checked read
void vec_free(Vec *v);              // free data, reset fields
int vec_pop(Vec *v, int *out);

int main(){
    Vec v1;
    if (vec_init(&v1) != 0) return 1;
    printf("len=%ld cap=%ld\n", v1.len, v1.cap);
    for (int i = 0; i < 10; i++) {
      if (vec_push(&v1, i * 10) != 0) {}
    }
    printf("len=%ld cap=%ld\n", v1.len, v1.cap);

    for(size_t i =0;i<v1.len;i++){
        printf("Element %ld = %d\n",i+1,v1.data[i]);
    }
    int val;
    if (vec_get(&v1, 3, &val) == 0) printf("v[3] = %d\n", val);   // 30
    if (vec_get(&v1, 12, &val) != 0) printf("v[12] out of range\n");
    vec_free(&v1);
    vec_push(&v1, 5);        // push after free
    printf("len=%zu cap=%zu\n", v1.len, v1.cap);
    int top;
    if (vec_pop(&v1, &top) == 0) {
        printf("popped %d\n", top);   // safe: top is valid
    } else {
        printf("empty\n");            // top is NOT valid, don't use it
    }
    printf("len=%zu\n", v1.len);                 // expect 0
    if (vec_pop(&v1, &top) != 0) printf("pop on empty: -1\n");

    vec_free(&v1);

    return 0;
}

int vec_push(Vec *v, int x){
    if(v->len == v->cap){
        size_t new_cap = v->cap ? v->cap * 2 : 4;
        int *tmp = realloc(v->data, new_cap * sizeof *tmp);
        if(tmp == NULL) return -1;
         v->data = tmp; 
         v->cap = new_cap;
        }
        v->data[v->len] = x;
        v->len++;
        return 0;
}

int vec_init(Vec *v){
    int *tmp = malloc(sizeof(int)*4);
    if (tmp == NULL) return -1;
    v->data = tmp;
    v->cap  = 4;
    v->len = 0;
    return 0;
}

void vec_free(Vec *v){
    free(v->data);
    v->data = NULL;
    v->len = (size_t)0;
    v->cap = (size_t)0;
}

int vec_get(const Vec *v, size_t i, int *out){
    if(i >= v->len){
        return -1;
    }
    *out = v->data[i];
    return 0;
}

int vec_pop(Vec *v, int *out){
    if(v->len == 0) return -1;
    v->len--;
    *out = v->data[v->len];
    return 0;
}
