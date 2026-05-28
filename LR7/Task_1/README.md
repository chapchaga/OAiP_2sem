# Lab7_Task1 — Doubly Linked Queue (Variant 5 / #20)

## Task
Represent program text as a doubly linked queue of strings.
Specify start and end line numbers. Move that block of lines to a chosen position in the queue.

## Prerequisites
- Qt6 (install via Homebrew: `brew install qt`)
- CMake 3.16+
- A C++17 compiler (Xcode CLT)

## Build & Run

```bash
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=$(brew --prefix qt)
cmake --build .
./Lab7_Task1
```

## How to use
1. **Load from file** — opens any text file; each line becomes a node in the queue.
2. **Push Back / Push Front** — add a typed line to the end or beginning.
3. **Pop Front / Pop Back** — remove from beginning or end.
4. **Clear** — empty the queue.
5. **Move Block** — enter *Start line*, *End line*, and *Insert after position* (0 = move to front), then click **Move Block**.
