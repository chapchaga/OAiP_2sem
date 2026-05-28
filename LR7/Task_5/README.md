# Lab7 Task5 — MyDeque

## Сборка (macOS + Qt6 + VS Code)

```bash
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=$(brew --prefix qt6)
cmake --build .
```

Если Qt6 установлен через Homebrew:
```bash
brew install qt6
```

Затем запустить:
```bash
./Lab7_Task5.app/Contents/MacOS/Lab7_Task5
```

## Реализованные операции

| Метод | Сложность |
|-------|-----------|
| push_back | O(1) amortized |
| push_front | O(1) amortized |
| pop_back | O(1) |
| pop_front | O(1) |
| operator[] | O(1) |
| clear | O(n) |
| size / empty | O(1) |

Iterator не инвалидируется при resize — хранит указатели на блоки через map.
