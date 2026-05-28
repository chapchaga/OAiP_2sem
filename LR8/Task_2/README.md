# Lab8 Task2 — Binary Heap (Array + List)

## Требования
- Qt Creator с Qt6
- CMake >= 3.16

## Как открыть в Qt Creator

**Открывай именно корневой файл:**
```
File → Open File or Project → выбери Lab8_Task2/CMakeLists.txt
```

Не открывай `App/CMakeLists.txt` — только корневой.

## Сборка через терминал (macOS)

```bash
brew install qt6
cd Lab8_Task2 && mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=$(brew --prefix qt6)
cmake --build .
./HeapApp
```

## Структура

```
Lab8_Task2/
├── CMakeLists.txt          ← ОТКРЫВАТЬ ИМЕННО ЭТОТ
├── ArrayHeap/              ← статическая библиотека (libArrayHeap.a)
│   ├── ArrayHeap.h
│   └── ArrayHeap.cpp
├── ListHeap/               ← динамическая библиотека (libListHeap.dylib)
│   ├── ListHeap.h          ← использует weak_ptr
│   └── ListHeap.cpp
└── App/
    ├── ui/mainwindow.ui    ← Qt UI файл
    └── src/
        ├── main.cpp
        ├── mainwindow.h
        └── mainwindow.cpp
```
