Absolutely. We should create proper study notes before moving forward. You should be able to revisit these notes later without needing to read our entire conversation again.

I'll consolidate what we've learned in Chapter 1 so far, particularly the **C compilation process**, and explain:

- What each stage does.
- Which program/tool performs it.
- Where it executes.
- What files it produces.
- Where those files are stored.
- How the resulting data is represented.
- What happens when the executable runs.

I'll also include Linux commands and practical examples.

# **Chapter 1 — C Fundamentals**

## **Notes 1: From C source code to program execution**



Study notes

Linux + GCC



## **1. The complete journey**

When you write a C program, the CPU cannot directly execute the C source code.

The source code must go through several stages before execution.

[Maíra Canal | About Kernel Symbol Table, Compilation, and more](https://images.openai.com/static-rsc-4/8_YF_48rlFqId_nWFWXPEdlc66NZzcoUDPYPiyHpFl-gFWEsXH2vSdd-9TnODuznxwAnZ9zVYkj2yFO6pQTAUmpnOte3j4HqSqQ58dQ75VAdwnOOZdDGiZyJgxcrofMR0ozMEhFYQglvt8vERM-mIZFO0-FCk9-YvAidfbXj4yw?purpose=inline)

[mairacanal.github.io](https://mairacanal.github.io/kernel-symbol-table-compilation-more/?utm_source=chatgpt.com)

The complete process:

```
       main.c
          |
          v
    PREPROCESSING
          |
          v
        main.i
          |
          v
     COMPILATION
          |
          v
        main.s
          |
          v
      ASSEMBLY
          |
          v
        main.o
          |
          v
       LINKING
          |
          v
         main
          |
          v
       LOADING
          |
          v
       EXECUTION
          |
          v
          CPU
```

There are four main compilation stages, followed by loading and execution.

## **2. Stage 1 — Preprocessing**

Tool: C preprocessor

**Purpose:** Process preprocessor directives before actual compilation begins.

Consider our program:

```
#include <stdio.h>

#define VALUE 30

int main() {
    printf("%d\n", VALUE);
    return 0;
}
```

### **What does it do?**

It handles instructions beginning with `#`.

| Directive  | Responsibility           |
| ---------- | ------------------------ |
| `#include` | Includes header contents |
| `#define`  | Defines macros           |
| `#ifdef`   | Conditional compilation  |
| `#ifndef`  | Conditional compilation  |
| `#endif`   | Ends a conditional block |

For example:

```
#define VALUE 30

int x = VALUE;
```

After macro expansion, it becomes conceptually:

```
int x = 30;
```

### **Where does preprocessing happen?**

- **Who performs it?** C preprocessor (`cpp`).
- **Where does it execute?** Your computer's CPU.
- **Where does it work?** In memory, processing the source text.
- **Where is the output stored?** In a file if you request one, otherwise typically in a temporary pipeline between compiler stages.

### **How to see it**

```
gcc -E main.c -o main.i
```

Now:

```
less main.i
```

You'll see expanded header contents and your preprocessed program.

**Stage 1 summary**

| Property                | Answer                 |
| ----------------------- | ---------------------- |
| Input                   | `main.c`               |
| Output                  | `main.i`               |
| Tool                    | Preprocessor           |
| Output type             | Expanded C source text |
| Stored as               | Text file              |
| Machine code generated? | No                     |

**Important:** `stdio.h` provides declarations such as the declaration of `printf()`. It does not provide the actual implementation of `printf()`.

## **3. Stage 2 — Compilation**

Tool: C compiler

**Purpose:** Translate preprocessed C code into assembly language.

For example:

```
int main() {
    int x = 20;
    int y = 10;
    int result = x + y;

    return result;
}
```

The compiler analyzes the code and generates instructions for your target processor.

Conceptually, the output might resemble:

```
movl $20, %eax
addl $10, %eax
```

This is illustrative assembly, not necessarily the exact output for your program.

### **What happens internally?**

The compiler performs several operations:

1. Lexical analysis: identifies tokens.
2. Parsing: checks the program's grammatical structure.
3. Semantic analysis: checks types, declarations and other language rules.
4. Intermediate representation (IR): represents the program internally.
5. Optimization: improves generated code where appropriate.
6. Code generation: produces target assembly.

### **Where does compilation happen?**

- **Who performs it?** Compiler (GCC uses its compiler frontend and backend, including `cc1` for C).
- **Where does it execute?** CPU.
- **Where does it work?** Compiler data structures and intermediate representations reside in RAM while the compiler runs.
- **Where is output stored?** In a file when requested.

### **How to see it**

```
gcc -S main.c -o main.s
```

Inspect:

```
less main.s
```

**Stage 2 summary**

| Property                | Answer                 |
| ----------------------- | ---------------------- |
| Input                   | Preprocessed C source  |
| Output                  | `main.s`               |
| Tool                    | Compiler               |
| Output type             | Assembly language      |
| Stored as               | Text file              |
| Machine code generated? | Not yet in this output |

**Important:** Assembly language is a human-readable representation of processor instructions. The CPU does not directly execute the assembly text file.

## **4. Stage 3 — Assembly**

Tool: Assembler

**Purpose:** Convert assembly instructions into machine code.

Let's take an assembly instruction:

```
movl $20, %eax
```

The assembler converts it into the processor's encoded instruction bytes.

These bytes represent an instruction the CPU can execute.

### **What is machine code?**

Machine code is encoded instructions represented as binary data.

For example, an instruction might be represented using hexadecimal bytes:

```
B8 14 00 00 00
```

The exact encoding depends on the processor architecture and instruction.

### **Where does assembly happen?**

- **Who performs it?** Assembler (`as`).
- **Where does it execute?** CPU.
- **Where does it work?** RAM while assembling.
- **Where is output stored?** In an object file on disk.

### **How to see it**

```
gcc -c main.c -o main.o
```

Inspect the file:

```
file main.o
```

You will typically see something similar to:

```
ELF 64-bit LSB relocatable, x86-64
```

Your exact result depends on your system.

Now inspect its instructions:

```
objdump -d main.o
```

This command disassembles the machine code into a readable assembly representation.

### **What is inside&#x20;**`main.o`**?**

A relocatable object file typically contains:

- Machine-code sections.
- Data sections.
- Symbol information.
- Relocation information.
- Debugging information, if generated.

Why relocation information?

Because the final addresses of functions and data might not yet be known.

For example, your object file might contain a reference to `printf()`, but it doesn't contain the C library implementation itself.

**Stage 3 summary**

| Property                        | Answer                 |
| ------------------------------- | ---------------------- |
| Input                           | `main.s`               |
| Output                          | `main.o`               |
| Tool                            | Assembler              |
| Output type                     | ELF relocatable object |
| Stored as                       | Binary file            |
| Ready to execute independently? | Usually no             |

**Remember:** `main.o` contains machine code, but machine code alone does not necessarily make a complete executable.

## **5. Stage 4 — Linking**

Tool: Linker

**Purpose:** Combine object files and resolve references between them and required libraries.

Consider:

```
#include <stdio.h>

int main() {
    printf("Hello World\n");
    return 0;
}
```

Your program uses `printf()`.

But the actual implementation comes from the C standard library.

### **What happens during linking?**

Suppose you have:

```
main.o
math.o
```

Both are object files.

You might have a function defined in `math.o` that is called from `main.o`.

The linker combines these object files and resolves references between them.

It also handles library dependencies and relocation.

### **Where does linking happen?**

- **Who performs it?** Linker (`ld`), usually invoked through GCC.
- **Where does it execute?** CPU.
- **Where does it work?** RAM while linking.
- **Where is output stored?** Executable file on disk.

### **How to perform linking**

```
gcc main.o -o main
```

Now inspect:

```
file main
```

On a typical modern Linux system, you will see an ELF executable.

### **Static vs dynamic linking**

There are two important approaches.

**Static linking**

Required library code is incorporated into the executable.

**Dynamic linking**

The executable references shared libraries that are loaded at runtime.

For example, on Linux, your executable may depend on:

```
libc.so.6
```

You can inspect dependencies using:

```
ldd main
```

**Stage 4 summary**

| Property              | Answer                                  |
| --------------------- | --------------------------------------- |
| Input                 | `main.o` and required objects/libraries |
| Output                | `main`                                  |
| Tool                  | Linker                                  |
| Output type           | Executable ELF                          |
| Stored as             | Binary file                             |
| Ready for OS loading? | Yes                                     |

**Important distinction:** With dynamic linking, the linker arranges references to shared libraries, and the dynamic loader performs the necessary runtime loading and symbol resolution.

## **6. Stage 5 — Loading**

Component: Operating system and dynamic loader

We now have an executable file.

But the executable is still stored on your hard disk (or SSD).

How does it start running?

You execute:

```
./main
```

The operating system creates a process and arranges for the executable to be loaded into its virtual address space.

### **What does the OS do?**

1. Creates the process and its execution context.
2. Maps executable code and data into virtual memory.
3. Sets up the process's initial stack and arguments.
4. Arranges for required shared libraries to be loaded.
5. Transfers control to the program's entry point.

On Linux, ELF executables are loaded using the kernel's executable-loading mechanism. Dynamically linked programs also involve a dynamic linker/loader.

### **Where is the program stored now?**

An important distinction:

- The executable file remains on disk.
- Its code and data are mapped into the process's virtual address space.
- Physical RAM pages are made available as needed, often through demand paging.
- Some pages may be shared, such as read-only library code.

[Memory Layout of a Program(Process)](https://images.openai.com/static-rsc-4/jh5qhYe9ipxEGyQ7TyTovuRKfKSaT-cskMu4lDgpD0kRr8GJT6XzVXkedB1O_-cTr0iof3IyHOT8u2tHZKoW8XSB636lc4T2dSvOE5IsBQ6Q5-HsiUnmq-FiYBbbhW7Qxdh66ilbtAWFop74aFUsBsea-fCrFqS6lbv9nl4cLo4?purpose=inline)

[beginthread.tistory.com](https://beginthread.tistory.com/153?utm_source=chatgpt.com)

**Stage 5 summary**

| Property               | Answer                                          |
| ---------------------- | ----------------------------------------------- |
| Input                  | Executable `main`                               |
| Responsible            | OS kernel and dynamic loader                    |
| Output                 | Running process                                 |
| Memory                 | Virtual address space mapped to physical memory |
| CPU execution started? | Yes, after control is transferred               |

## **7. Stage 6 — Execution**

Component: CPU

Finally, the CPU executes the machine instructions.

Consider:

```
int x = 20;
int y = 10;
int result = x + y;

printf("%d\n", result);
```

Conceptually, the CPU performs operations corresponding to:

1. Obtain the value of `x`.
2. Obtain the value of `y`.
3. Perform addition.
4. Store or otherwise maintain the result.
5. Execute the instructions needed to call `printf()`.

The actual instructions and use of registers depend on compiler optimization.

### **What happens inside the CPU?**

[File:The Fetch-Execute Cycle.svg - Wikimedia Commons](https://images.openai.com/static-rsc-4/6HXlE29ED0fAeDFCOE8QXQlR_vE3JD0t7P8LvgfTSlCOrlKJl6De4WDFtxZck27p_TN6CQr4u5qgTZWWSjGHTV6uCA4IxWveJGZ3OGL-ynoObw9rWMjalzaHyovdy5KekfYVrYJBniersfNi0fbh2qQLB-NTTFkdrnV2wCHLKeI?purpose=inline)

[commons.wikimedia.org](https://commons.wikimedia.org/wiki/File%3AThe_Fetch-Execute_Cycle.svg?utm_source=chatgpt.com)

The CPU repeatedly performs an instruction cycle:

1. **Fetch:** Obtain the next instruction.
2. **Decode:** Determine what the instruction means.
3. **Execute:** Perform the operation.
4. **Repeat:** Continue with subsequent instructions.

Important CPU components:

| Component    | Responsibility                                                 |
| ------------ | -------------------------------------------------------------- |
| Control unit | Coordinates instruction execution                              |
| ALU          | Performs arithmetic and logical operations                     |
| Registers    | Hold values needed by the CPU                                  |
| Cache        | Stores frequently accessed data/instructions closer to the CPU |

### **Where does execution happen?**

- **Who performs it?** CPU.
- **Where are instructions stored?** In the process's memory mapping, backed by the executable and potentially cached in RAM.
- **Where are active values stored?** CPU registers, cache and RAM, depending on the operation and compiler.
- **Where does output go?** `printf()` writes formatted output to standard output, which is typically connected to your terminal.

**Stage 6 summary**

| Property     | Answer                      |
| ------------ | --------------------------- |
| Input        | Loaded program instructions |
| Responsible  | CPU                         |
| Output       | Program behavior/results    |
| Execution    | Fetch, decode and execute   |
| Final output | `30` in your example        |

# **8. Complete comparison — Where does everything happen?**

This is probably the most important table in these notes. Save it.

| Stage         | Responsible component | Input                    | Output                  | Output stored as                   |
| ------------- | --------------------- | ------------------------ | ----------------------- | ---------------------------------- |
| Preprocessing | Preprocessor          | C source                 | Expanded C              | Text file                          |
| Compilation   | Compiler              | Expanded C               | Assembly                | Text file                          |
| Assembly      | Assembler             | Assembly                 | Machine code + metadata | Object file                        |
| Linking       | Linker                | Object files + libraries | Executable              | Binary file                        |
| Loading       | OS + dynamic loader   | Executable               | Running process         | Virtual memory mappings            |
| Execution     | CPU                   | Machine instructions     | Program operations      | Registers, cache and RAM as needed |

## **9. Important: Where are the tools themselves stored?**

You asked an excellent question earlier about where memory actually exists.

Let's distinguish three things:

**1. Tools**

GCC, the assembler and linker are themselves programs installed on your Linux filesystem.

For example:

```
which gcc
which as
which ld
```

**2. Working memory**

When you execute GCC, the OS loads the required executable code and data into memory. The compiler also creates temporary data structures in its process memory.

**3. Generated files**

Files such as `main.i`, `main.s`, `main.o` and `main` are stored on your filesystem, not permanently inside RAM.

The OS and filesystem manage how their data is stored on your SSD or other storage device.

## **10. Practical commands — Your revision sheet**

Keep this table handy.

| Command                   | Purpose                      |
| ------------------------- | ---------------------------- |
| `gcc -E main.c -o main.i` | Preprocess                   |
| `gcc -S main.c -o main.s` | Generate assembly            |
| `gcc -c main.c -o main.o` | Generate object file         |
| `gcc main.o -o main`      | Link                         |
| `./main`                  | Execute                      |
| `file main.o`             | Inspect file format          |
| `objdump -d main.o`       | Disassemble object code      |
| `nm -u main.o`            | Inspect undefined symbols    |
| `ldd main`                | Inspect dynamic dependencies |

You can also use:

```
gcc -save-temps main.c -o main
```

This asks GCC to retain intermediate files produced during compilation.

# **11. Important terminology**

Make sure you understand these terms before proceeding.

| Term            | Meaning                                       |
| --------------- | --------------------------------------------- |
| Source code     | Human-written C program                       |
| Preprocessor    | Processes directives                          |
| Compiler        | Translates C into target instructions         |
| Assembly        | Human-readable processor instructions         |
| Assembler       | Converts assembly into machine code           |
| Machine code    | Encoded processor instructions                |
| Object file     | Machine code plus metadata                    |
| Linker          | Combines object files and resolves references |
| Executable      | Linked program ready for loading              |
| Loader          | Arranges executable execution                 |
| Process         | Running instance of a program                 |
| Dynamic library | Shared library loaded at runtime              |
| Disassembly     | Machine code represented as readable assembly |

# **12. Self-assessment**

Before we move forward, I want to ensure these notes have actually helped you understand the entire process.

**Chapter 1 — Compilation assessment**

6 questions

**Q1. Which component processes #include and #define?**

A. Compiler

B. Preprocessor

C. Assembler

D. Linker

**Q2. Which stage converts C code into assembly?**

A. Preprocessing

B. Compilation

C. Assembly

D. Linking

**Q3. What does main.o contain?**

A. Only C source code

B. Machine code and object-file metadata

C. A running process

D. Only assembly text

**Q4. Which stage combines object files?**

A. Preprocessing

B. Compilation

C. Linking

D. Loading

**Q5. Where does the OS arrange a process's executable code to be accessed?**

A. Only CPU registers

B. Virtual address space mapped to memory

C. Only hard disk

D. Only CPU cache

**Q6. Who executes machine instructions?**

A. Linker

B. Assembler

C. CPU

D. Preprocessor

Submit answers

**My recommendation:** Don't move to memory layout just yet. Complete this assessment and make sure you can explain the compilation pipeline without looking at the notes.

After that, we'll cover the next Chapter 1 topic: C program memory layout — text segment, data segment, BSS, heap and stack. That will connect everything we've learned about processes, RAM, pointers and execution.

One chapter at a time, but we'll keep our weekend deadline in sight.