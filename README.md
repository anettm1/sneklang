# Snaklang — Reference-Counted Object System in C

This project implements the **object system and reference-counted garbage collector** for **Snaklang**, a toy programming language written in C.
It provides a minimal runtime capable of creating and managing typed values like integers, floats, strings, vectors, and arrays — all with **automatic memory management** using **reference counting**.

---

## Objective

The goal of this project was to **learn and practice manual memory management in C**, including **reference counting, heap allocation, and safe object ownership patterns**.
It was developed as part of the **“Learn memory management in C” course by [Boot.dev](https://www.boot.dev)**.

---

## Features

- **Five core object types**
  - `INTEGER`, `FLOAT`, `STRING`, `VECTOR3`, and `ARRAY`
- **Reference counting garbage collector**
  - Objects track their `refcount`
  - Automatically freed when `refcount` reaches zero
- **Nested object support**
  - Vectors and arrays hold other `snek_object_t` instances safely
- **Operator overloading**
  - `snek_add()` adds compatible objects (`int+float`, `string+string`, `vector+vector`, `array+array`, etc.)
- **Length calculation**
  - `snek_length()` returns length/size depending on object kind
- **Array utilities**
  - `snek_array_get()` / `snek_array_set()`

---

## Project Structure

```
├── main.c             # Demonstrates all features
├── snekobject.h       # Type definitions and function declarations
└── snekobject.c       # Implementation of all runtime and GC logic
```

---

## Core Design

### Reference Counting
Each `snek_object_t` has an integer `refcount`.
When you create a new object via `new_snek_*()`, it starts with `refcount = 1`.

```
snek_object_t *num = new_snek_integer(42);
refcount_dec(num); // Frees automatically when refcount hits 0
```

- `refcount_inc(obj)` → increases ownership
- `refcount_dec(obj)` → decreases ownership and frees if `refcount == 0`
- `refcount_free(obj)` → recursively frees strings, vectors, arrays, etc.

### Example: Vector and Array Memory Rules
- **VECTOR3**: Holds *references* to other objects (`x`, `y`, `z`).
  Uses `refcount_inc()` / `refcount_dec()` — never `free()` directly.
- **ARRAY**: Owns a heap-allocated `elements` buffer (freed with `free()`),
  but each element is a refcounted child object.

---

## Example Output

Running `main.c` prints something like:

```
Int: 2
Float: 3.50
String: My name is Snek.
Vector[1st el.]: 2
Vector[2nd el.]: 2.40
Vector[3rd el.]: hello user
Array kind: 4
Array size: 2
Array[1st el.]: hi
Array[2nd el.]: 2
Length of msg: 12
Add integers: 6
Add floats: 9.50
Add strings: hello world!
Vector3 sum: 5 7 9
Array(1st el.): 1
Array(5th el.): hello
```

---

## Build & Run

### Compile:
```
gcc -std=c17 -Wall -Wextra -pedantic main.c snekobject.c -o snaklang
```

### Run:
```
./snaklang
```

Use AddressSanitizer for debugging:
```
gcc -std=c17 -Wall -Wextra -pedantic -fsanitize=address,undefined -g main.c snekobject.c -o snaklang
./snaklang
```

---

## Future Plans

- Add dictionary (`HASHMAP`) object type
- Implement proper operator dispatch (`snek_sub`, `snek_mul`, etc.)
- Possibly change to Mark and Sweep GC