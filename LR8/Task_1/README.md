# Lab8 Task1 — Binary Search Tree (Qt6 + CMake)

## Требования
- Qt 6.x
- CMake 3.16+
- Компилятор с поддержкой C++17 (clang++ на macOS)

## Сборка

```bash
cd Lab8_Task1
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=$(brew --prefix qt6)
cmake --build .
./Lab8_Task1
```

Если Qt установлен через Qt Installer, укажи путь вручную:
```bash
cmake .. -DCMAKE_PREFIX_PATH=/path/to/Qt/6.x.x/macos
```

## Реализованные операции

| Операция | Описание |
|----------|----------|
| `add(v)` | Добавление нового узла |
| `remove(v)` | Удаление узла по значению |
| `find(v)` | Поиск узла по значению |
| `traverse()` | Обход inorder (возвращает отсортированный список) |
| `insertSubtree` | Вставка поддерева к указанному родителю |
| `removeSubtree` | Отсоединение поддерева с заданным корнем |
| `removeBranch` | Удаление ветви (узел + все потомки) |
| `insertAt` | Вставка элемента в конкретную позицию |
| `LCA(a, b)` | Поиск наименьшего общего предка двух узлов |
