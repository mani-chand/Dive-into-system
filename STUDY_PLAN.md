# Dive Into Systems — Study Plan (v2, fast track)

Book: https://diveintosystems.org/book/ (Matthews, Newhall, Webb)
Pace: 6 h/week, about 15 weeks. Prior knowledge: C++ (pointers, classes, threads, mutexes), new to C memory management.
Assembly track: x86-64 (ch. 7). Skip ch. 8 (32-bit). Use ch. 9 only if on ARM.
Teaching mode: lessons are taught in chat (predict, type, run, report). The book is a reference.

## Weekly rhythm (6 h)
- 2 h: lesson / reading.
- 2 h: type every example and run it. Do not paste.
- 1.5 h: exercises / mini project.
- 0.5 h: notes in `notes/chNN.md`.

## Done
- Setup: gcc 9.4, gdb 9.2, make 4.2.1, valgrind 3.15.0.
- Week 1: terminal, `printf`, variables, integer division, `if`, loops, functions, Makefile, arrays, structs.

## Schedule

| Week | Topic | Checkpoint |
|---|---|---|
| 1 | DONE: Unix, Ch 1 basics | Makefile build, `arr_sum`, `arr_max` |
| 2 | Ch 2: pointers, stack vs heap, `malloc`/`free`, Valgrind leaks | Pointer-swap, leak found and fixed in Valgrind |
| 3 | Ch 2: strings, 2D arrays, C libraries, `scanf` | Own growable `vector` in C |
| 4 | Ch 3: GDB, Valgrind, sanitizers | Find planted bugs with GDB and Valgrind |
| 5 | Ch 4 (a): binary, hex, signed ints, overflow | Hand-convert, verify in C |
| 6 | Ch 4 (b): bitwise ops, endianness, floating point | Bit helpers: set/clear/count |
| 7 | Ch 5 (a): gates, circuits, ALU | Draw a 1-bit adder |
| 8 | Ch 5 (b): CPU, pipelining | Explain fetch-decode-execute-writeback |
| 9 | Ch 6 + Ch 7 (a): assembly intro, instructions | `gcc -S`, read a simple function |
| 10 | Ch 7 (b): control flow, functions, structs, buffer overflow | Trace a function in GDB by instruction |
| 11 | Ch 10 + review | Read a 20-line function's asm unaided |
| 12 | Ch 11: memory hierarchy, locality, cache | Row vs column matrix timing |
| 13 | Ch 12: compiler optimization | `-O0` vs `-O2` asm and timing |
| 14 | Ch 13: processes, `fork`/`exec`, virtual memory, signals, pipes | Tiny shell |
| 15 | Ch 14: Pthreads, races, synchronization, OpenMP | Parallel sum, trigger and fix a race |

Optional after week 15: Ch 15 (GPUs, distributed), Ch 9 (ARM).

## Mini projects
1. After wk 4: own `vector` + tests, clean under Valgrind.
2. After wk 6: bit-twiddling library with tests.
3. After wk 11: annotate assembly of a function you wrote.
4. After wk 13: cache and optimization benchmark report.
5. After wk 15: Pthreads program with speedup measurements.

## Progress log
- [x] Setup
- [x] Wk 1  - [x] Wk 2  - [ ] Wk 3  - [ ] Wk 4
- [ ] Wk 5  - [ ] Wk 6  - [ ] Wk 7  - [ ] Wk 8
- [ ] Wk 9  - [ ] Wk 10 - [ ] Wk 11
- [ ] Wk 12 - [ ] Wk 13
- [ ] Wk 14 - [ ] Wk 15

## Done so far in Week 3
- Strings, `fgets`/`strtol` safe input, guess game (`code/guess.c`).
- Mini project 1 (vector): `code/vec.c` with init/push/get/pop/free, Valgrind clean.
- Review checklist: `notes/c_review_checklist.md`.
- Left in Week 3: 2D arrays, C libraries / multi-file build.

## Known gaps to revisit
- Second `make` run ("up to date") not yet seen.
- `size_t` vs `int`, `||` vs `?:`: both bit us in `vec_push`. Re-check in reviews.
