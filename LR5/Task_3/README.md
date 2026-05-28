# BitSet Visualizer — Qt Creator Project

## Файлы проекта

| Файл | Описание |
|---|---|
| `BitSetVisualizer.pro` | Qt-проект (открыть в Qt Creator) |
| `bitset.h` | Заголовок класса BitSet |
| `bitset.cpp` | Реализация класса BitSet |
| `mainwindow.h` | Заголовок главного окна |
| `mainwindow.cpp` | Реализация UI + тесты |
| `main.cpp` | Точка входа |

## Как открыть в Qt Creator

1. Откройте Qt Creator
2. File → Open File or Project → выберите `BitSetVisualizer.pro`
3. Настройте kit (Qt 5.x или Qt 6.x + компилятор с поддержкой C++17)
4. Нажмите ▶ Run

## Архитектура класса BitSet

Биты хранятся в `std::vector<uint64_t>` — в каждом элементе 64 бита.

- Размер вектора: `⌈N/64⌉` элементов
- Позиция бита `i`: chunk = `i/64`, маска = `1 << (i%64)`
- Операции `~`, `&`, `|`, `^` итерируют по всем chunk-ам → **O(N/64)**
- `test`, `set`, `reset`, `flip(pos)`, `count` (через `__builtin_popcountll`) — **O(1)** per chunk
- `count()` суммирует по всем chunk-ам — **O(N/64)**

## Функции BitSet

| Функция | Описание | Сложность |
|---|---|---|
| `all()` | Все биты == 1 | O(N/64) |
| `any()` | Хотя бы один бит == 1 | O(N/64) |
| `none()` | Ни один бит не == 1 | O(N/64) |
| `count()` | Количество единичных битов | O(N/64) |
| `flip()` | Инверсия всех битов | O(N/64) |
| `flip(pos)` | Инверсия бита на позиции | O(1) |
| `reset()` | Все биты = 0 | O(N/64) |
| `reset(pos)` | Бит на позиции = 0 | O(1) |
| `set()` | Все биты = 1 | O(N/64) |
| `set(pos)` | Бит на позиции = 1 | O(1) |
| `size()` | Размер (N) | O(1) |
| `test(pos)` | Значение бита на позиции | O(1) |
| `to_string()` | Строковое представление | O(N) |
| `to_ulong()` | Преобразование в unsigned long | O(1) |
| `to_ullong()` | Преобразование в unsigned long long | O(1) |
| `operator~` | Побитовое НЕ | O(N/64) |
| `operator&` | Побитовое И | O(N/64) |
| `operator\|` | Побитовое ИЛИ | O(N/64) |
| `operator^` | Побитовое XOR | O(N/64) |
| `operator[]` | Доступ/запись по индексу | O(1) |
