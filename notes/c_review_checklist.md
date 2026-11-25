# C code review checklist: bad patterns to spot

Format: BAD code, why it is bad, what to ask in review, FIX.
Items marked [SEEN] are bugs you already reproduced in this course.
Severity: CRIT = likely security hole or data corruption, HIGH = crash or leak, MED = latent bug.

---

## 1. Memory: heap

### 1.1 Missing `free` (leak) [SEEN] HIGH
```c
int *p = malloc(sizeof(int));
*p = 42;
return 0;                 // never freed
```
Ask: for every `malloc`, where is the matching `free`, on every path including early `return` and error paths?
Fix: free once, on all paths. Valgrind shows `definitely lost`.

### 1.2 Unchecked `malloc` HIGH
```c
int *p = malloc(n * sizeof(int));
p[0] = 1;                 // crashes if p is NULL
```
Fix: `if (p == NULL) { /* handle */ }`.

### 1.3 Use after free [SEEN] CRIT
```c
free(a);
printf("%d\n", a[0]);
```
Ask: is the pointer used after `free`? Is it set to `NULL`?
Fix: `free(a); a = NULL;` so a mistake crashes loudly.

### 1.4 Double free CRIT
```c
free(a);
free(a);
```
Fix: set to `NULL` after `free` (`free(NULL)` is safe).

### 1.5 Heap overflow [SEEN] CRIT
```c
int *a = malloc(3 * sizeof(int));
a[3] = 4;                 // indexes are 0..2
```
Ask: what is the allocated size, and what is the max index used?

### 1.6 Wrong size in `malloc` HIGH
```c
int *a = malloc(10);              // 10 bytes, not 10 ints
char *s = malloc(strlen(t));      // forgot +1 for '\0'
```
Fix: `malloc(10 * sizeof *a)` and `malloc(strlen(t) + 1)`.

### 1.7 Integer overflow in size calculation CRIT
```c
size_t total = count * size;      // can wrap around, tiny allocation
```
Ask: can `count * size` overflow when input is attacker-controlled?

---

## 2. Memory: stack and pointers

### 2.1 Returning address of a local [SEEN] CRIT
```c
int *f(void) { int x = 7; return &x; }
```
Compiler warns. Never ignore it.

### 2.2 Pointer from a plain integer [SEEN] HIGH
```c
int *p = 10;              // address 10, not value 10
```
Warning: `-Wint-conversion`.

### 2.3 Uninitialized pointer or variable HIGH
```c
int *p;
*p = 5;                   // p holds garbage
int n;
printf("%d\n", n);        // garbage
```
Fix: initialize at declaration, `int *p = NULL;`.

### 2.4 Missing NULL check before dereference MED
Ask: can this pointer be NULL here (failed `malloc`, missing argument, not-found lookup)?

---

## 3. Buffers and strings

### 3.1 Unbounded copy [SEEN] CRIT
```c
strcpy(dst, src);
sprintf(buf, "%s", input);
gets(buf);                // removed from C11, never use
```
Fix:
```c
snprintf(dst, sizeof dst, "%s", src);
fgets(buf, sizeof buf, stdin);
```
Ask: where does `src` come from? Who controls its length?

### 3.2 Off-by-one on strings [SEEN] CRIT
```c
char name[8];
strcpy(name, "ABCDEFGH");         // 8 chars + '\0' = 9 bytes
```
A string of length N needs N+1 bytes. Also `<=` where `<` is meant in loops.

### 3.3 Writing to a string literal [SEEN] HIGH
```c
char *p = "hello";
p[0] = 'j';               // segfault, read-only memory
```
Fix: `char p[] = "hello";` or `const char *p`.

### 3.4 Comparing strings with `==` [SEEN] MED
```c
if (a == b)               // compares addresses
```
Fix: `strcmp(a, b) == 0`.

### 3.5 Missing terminator after `strncpy` MED
`strncpy` does not add `\0` when the source is as long as `n`. Prefer `snprintf`.

### 3.6 Format string bug CRIT
```c
printf(user_input);       // attacker can use %s, %n
```
Fix: `printf("%s", user_input);`.

### 3.7 Array length lost in function [SEEN] HIGH
```c
int sum(int arr[]) { for (i = 0; i < 5; i++) ... }   // hardcoded 5
```
Fix: pass `len`, and check it. `sizeof arr` inside a function gives pointer size.

---

## 4. Integers

### 4.1 Integer division by mistake [SEEN] MED
```c
double avg = sum / count;         // both int: decimals dropped
```
Fix: `(double)sum / count`.

### 4.2 Signed overflow is undefined behavior HIGH
```c
int x = INT_MAX;
x + 1;                            // undefined, compiler may assume it never happens
```

### 4.3 Signed vs unsigned comparison HIGH
```c
int i = -1;
unsigned n = 5;
if (i < n)                        // false! -1 becomes huge
```
Compiler warns with `-Wsign-compare` (in `-Wextra`).

### 4.4 `=` instead of `==` MED
```c
if (x = 5)                        // assignment, always true
```
`-Wall` warns.

---

## 5. Control flow and logic

### 5.1 Missing `break` in `switch` MED
Fall-through runs the next case. Comment intentional fall-through.

### 5.2 Inverted condition [SEEN] MED
`n % 2` returns remainder, it is true for ODD. Compiler cannot catch meaning errors. Only tests do.

### 5.3 Unchecked return values MED
Ask: do `fopen`, `malloc`, `scanf`, `fgets`, `read`, `write` have their results checked?

---

## 6. Build and tooling red flags in a PR

- Compiled without `-Wall -Wextra`. Ask for it.
- Warnings ignored or silenced with a cast. Treat each warning as a bug.
- No test with boundary inputs: empty, length 0, length max, max+1.
- Not run under Valgrind or `-fsanitize=address,undefined`.
- Casting away `const`, or a cast added only to quiet the compiler.
- Magic numbers (`5`, `1024`) repeated instead of a named constant.

---

## Review routine (5 minutes per function)
1. Who owns each pointer? Who frees it? On every path?
2. For each buffer: size, max index, and where the length comes from.
3. Is every `malloc`, `fopen`, `read` result checked?
4. Is any input (argv, file, network) used as a length or index without a check?
5. Any pointer used after `free` or after its function returned?
6. Types: int vs unsigned, int vs size_t, int vs double division.
7. Run: `gcc -Wall -Wextra -g`, then Valgrind and ASan. A clean run does not prove correctness, but a dirty one proves a bug.

## Tool blind spots (from your own tests)
| Bug | Valgrind | ASan |
|---|---|---|
| Heap overflow / use-after-free / leak | yes | yes |
| Stack overflow past an object | no | yes |
| Overflow between fields inside one struct | no | no |
| Wrong logic (`n % 2` for even) | no | no |
