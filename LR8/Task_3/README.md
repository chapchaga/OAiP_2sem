# Lab 8 — Task 3

## Структура проекта

```
Lab8_Task3/
├── CMakeLists.txt
├── include/
│   ├── BSTNode.h       — узел BST с поддержкой двусвязного списка
│   ├── Map.h           — шаблонный Map<KeyType, ValueType> + два итератора
│   ├── Set.h           — шаблонный Set<KeyType> : public Map<KeyType, char>
│   ├── HashTable.h     — HashTable с функтором хеширования
│   └── MainWindow.h
├── src/
│   ├── main.cpp
│   └── MainWindow.cpp
└── ui/
    └── mainwindow.ui
```

## Сборка (macOS + Qt)

```bash
# Установить Qt если нет:
brew install qt

# Собрать:
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=$(brew --prefix qt)
cmake --build .
./Lab8_Task3
```

## Реализованный функционал

### Map<KeyType, ValueType>
- `insert(key, value)` — вставка/обновление
- `erase(key)` — удаление
- `contains(key)` — проверка наличия
- `operator[]` — доступ/создание (non-const и const)
- Итератор 1: обход дерева in-order через `treeNext()`
- Итератор 2: обход двусвязного списка через `node->next`

### Set<KeyType> : Map<KeyType, char>
- Наследует Map, фиктивный ValueType = char
- `insert(key)`, `erase(key)`, `contains(key)`
- Оба типа итераторов унаследованы

### HashTable<KeyType, ValueType, Hasher>
- `insert`, `erase`, `contains`, `clear`, `rehash`
- `operator[]` (non-const создаёт элемент, const бросает)
- Цепочки через `std::forward_list<std::pair<const KeyType, ValueType>>`
- Автоматический rehash при load factor > 0.75
- Принимает функтор хеширования как шаблонный аргумент
