#include "vector.h"
#include "pair.h"
#include "algorithms.h"

#include <iostream>
#include <stdexcept>
#include <string>

// 
//  Мини-фреймворк
// 
static int total = 0, passed = 0, failed = 0;
static std::string currentGroup;

void group(const std::string& name)
{
    currentGroup = name;
    std::cout << "\n┌─ " << name << "\n";
}

void check(bool cond, const std::string& desc)
{
    total++;
    if (cond)
    {
        passed++;
        std::cout << "│  ✓  " << desc << "\n";
    }
    else
    {
        failed++;
        std::cout << "│  ✗  FAIL: " << desc << "\n";
    }
}

// 
//  Vector — конструкторы
// 
void test_constructors()
{
    group("Vector — конструкторы");

    // Конструктор по умолчанию
    Vector<int> v;
    check(v.size()     == 0,     "default ctor: size == 0");
    check(v.capacity() == 0,     "default ctor: capacity == 0");
    check(v.empty(),             "default ctor: empty() == true");

    // Конструктор с размером и значением
    Vector<int> v2(5, 7);
    check(v2.size() == 5,        "ctor(n,val): size == 5");
    check(v2[0]     == 7,        "ctor(n,val): [0] == 7");
    check(v2[4]     == 7,        "ctor(n,val): [4] == 7");

    // Конструктор из initializer_list
    Vector<int> v3 = {1, 2, 3, 4};
    check(v3.size() == 4,        "ctor(init_list): size == 4");
    check(v3[0]     == 1,        "ctor(init_list): [0] == 1");
    check(v3[3]     == 4,        "ctor(init_list): [3] == 4");

    // Копирующий конструктор
    Vector<int> v4 = v3;
    check(v4.size() == 4,        "copy ctor: size совпадает");
    check(v4[1]     == 2,        "copy ctor: значения скопированы");
    v4[0] = 99;
    check(v3[0]     == 1,        "copy ctor: независимая копия (deep copy)");

    // Оператор присваивания
    Vector<int> v5;
    v5 = v3;
    check(v5.size() == 4,        "operator=: size совпадает");
    check(v5[2]     == 3,        "operator=: значения скопированы");
    v5[0] = 99;
    check(v3[0]     == 1,        "operator=: независимая копия (deep copy)");

    // Самоприсваивание
    Vector<int> v6 = {10, 20};
    v6 = v6;
    check(v6.size() == 2,        "operator= self: size не изменился");
    check(v6[0]     == 10,       "operator= self: данные сохранены");
}

// 
//  Vector — size / capacity / empty / max_size
// 
void test_capacity_methods()
{
    group("Vector — size / capacity / empty / max_size");

    Vector<int> v;
    check(v.empty(),             "empty на пустом");
    check(v.size() == 0,         "size на пустом == 0");
    check(v.max_size() > 0,      "max_size > 0");

    v.push_back(1);
    check(!v.empty(),            "не пустой после push_back");
    check(v.size() == 1,         "size == 1 после push_back");
    check(v.capacity() >= 1,     "capacity >= size");

    // Ёмкость растёт удвоением
    v.push_back(2);
    size_t cap2 = v.capacity();
    check(cap2 >= 2,             "capacity >= 2 после двух push_back");

    // Ёмкость не уменьшается сама при pop_back
    v.pop_back();
    check(v.capacity() == cap2,  "capacity не уменьшается при pop_back");
}

// 
//  Vector — reserve
// 
void test_reserve()
{
    group("Vector — reserve");

    Vector<int> v;
    v.reserve(20);
    check(v.capacity() >= 20,    "reserve(20): capacity >= 20");
    check(v.size()     == 0,     "reserve не меняет size");

    // Повторный reserve меньшего значения не уменьшает
    v.reserve(5);
    check(v.capacity() >= 20,    "reserve(5) не уменьшает capacity");

    // Данные не портятся после reserve + реаллокации
    for (int i = 0; i < 5; i++) v.push_back(i);
    v.reserve(100);
    check(v.size() == 5,         "reserve сохраняет size");
    check(v[0] == 0 && v[4]==4, "reserve сохраняет данные");
}

// 
//  Vector — resize
// 
void test_resize()
{
    group("Vector — resize");

    Vector<int> v = {1, 2, 3};

    // Расширение
    v.resize(6, 0);
    check(v.size() == 6,         "resize(6): size == 6");
    check(v[0]     == 1,         "resize: старые данные сохранены");
    check(v[3]     == 0,         "resize: новые элементы == 0");
    check(v[5]     == 0,         "resize: последний новый == 0");

    // Сужение
    v.resize(2, 0);
    check(v.size() == 2,         "resize(2): size == 2");
    check(v[0]     == 1,         "resize: [0] сохранён");
    check(v[1]     == 2,         "resize: [1] сохранён");

    // Resize с нестандартным значением
    v.resize(5, 42);
    check(v[2]     == 42,        "resize(5,42): новые элементы == 42");
}

// 
//  Vector — shrink_to_fit
// 
void test_shrink_to_fit()
{
    group("Vector — shrink_to_fit");

    Vector<int> v;
    v.reserve(100);
    for (int i = 0; i < 5; i++) v.push_back(i);

    check(v.capacity() >= 100,   "до shrink: capacity >= 100");
    v.shrink_to_fit();
    check(v.capacity() == v.size(), "после shrink: capacity == size");
    check(v.size()     == 5,     "shrink не меняет size");
    check(v[0]         == 0,     "shrink не портит данные");
    check(v[4]         == 4,     "shrink не портит данные [4]");
}

// 
//  Vector — push_back / emplace_back
// 
void test_push_emplace_back()
{
    group("Vector — push_back / emplace_back");

    Vector<int> v;
    v.push_back(10);
    check(v.size()  == 1,        "push_back: size == 1");
    check(v[0]      == 10,       "push_back: значение верно");

    v.push_back(20);
    v.push_back(30);
    check(v.size()  == 3,        "push_back x3: size == 3");
    check(v.back()  == 30,       "push_back: back() == 30");

    // Многократный push_back — проверяем реаллокацию
    Vector<int> v2;
    for (int i = 0; i < 100; i++) v2.push_back(i);
    check(v2.size() == 100,      "push_back x100: size == 100");
    check(v2[0]     == 0,        "push_back x100: [0] == 0");
    check(v2[99]    == 99,       "push_back x100: [99] == 99");

    // emplace_back
    v.emplace_back(99);
    check(v.back()  == 99,       "emplace_back: добавлено верное значение");
    check(v.size()  == 4,        "emplace_back: size увеличился");
}

// 
//  Vector — pop_back
// 
void test_pop_back()
{
    group("Vector — pop_back");

    Vector<int> v = {1, 2, 3};
    v.pop_back();
    check(v.size()  == 2,        "pop_back: size == 2");
    check(v.back()  == 2,        "pop_back: новый back == 2");

    v.pop_back();
    v.pop_back();
    check(v.empty(),             "pop_back до пустого: empty()");

    // pop_back на пустом — не крашится
    v.pop_back();
    check(v.size()  == 0,        "pop_back на пустом: size остаётся 0");
}

// 
//  Vector — insert / emplace
// 
void test_insert_emplace()
{
    group("Vector — insert / emplace");

    Vector<int> v = {1, 2, 3};

    // Вставка в середину
    v.insert(1, 99);
    check(v.size()  == 4,        "insert(1,99): size == 4");
    check(v[0]      == 1,        "insert: [0] == 1");
    check(v[1]      == 99,       "insert: [1] == 99");
    check(v[2]      == 2,        "insert: [2] == 2 (сдвинут)");
    check(v[3]      == 3,        "insert: [3] == 3 (сдвинут)");

    // Вставка в начало
    v.insert(0, 0);
    check(v[0]      == 0,        "insert(0): в начало");
    check(v[1]      == 1,        "insert(0): старый [0] сдвинут");

    // Вставка в конец
    size_t lastPos = v.size();
    v.insert(lastPos, 777);
    check(v.back()  == 777,      "insert в конец: back == 777");

    // emplace
    Vector<int> v2 = {10, 20, 30};
    v2.emplace(1, 15);
    check(v2[1]     == 15,       "emplace(1,15): [1] == 15");
    check(v2.size() == 4,        "emplace: size == 4");

    // insert за пределами — не крашится
    size_t oldSize = v.size();
    v.insert(9999, 42);
    check(v.size()  == oldSize,  "insert(9999): out-of-range игнорируется");
}

// 
//  Vector — erase
// 
void test_erase()
{
    group("Vector — erase");

    Vector<int> v = {10, 20, 30, 40, 50};

    // Удаление из середины
    v.erase(2);
    check(v.size()  == 4,        "erase(2): size == 4");
    check(v[0]      == 10,       "erase: [0] не изменился");
    check(v[2]      == 40,       "erase: [2] сдвинулся");
    check(v[3]      == 50,       "erase: [3] сдвинулся");

    // Удаление первого
    v.erase(0);
    check(v[0]      == 20,       "erase(0): новый [0] == 20");
    check(v.size()  == 3,        "erase(0): size == 3");

    // Удаление последнего
    v.erase(v.size() - 1);
    check(v.back()  == 40,       "erase последнего: back == 40");

    // erase за пределами — не крашится
    size_t oldSize = v.size();
    v.erase(9999);
    check(v.size()  == oldSize,  "erase(9999): out-of-range игнорируется");
}

// 
//  Vector — clear
// 
void test_clear()
{
    group("Vector — clear");

    Vector<int> v = {1, 2, 3, 4, 5};
    size_t cap = v.capacity();
    v.clear();

    check(v.size()      == 0,    "clear: size == 0");
    check(v.empty(),             "clear: empty() == true");
    check(v.capacity()  == cap,  "clear: capacity не меняется");

    // После clear можно снова push_back
    v.push_back(42);
    check(v.size()      == 1,    "после clear: push_back работает");
    check(v[0]          == 42,   "после clear: значение верно");
}

// 
//  Vector — assign
// 
void test_assign()
{
    group("Vector — assign");

    Vector<int> v = {1, 2, 3};
    v.assign(5, 7);

    check(v.size()  == 5,        "assign(5,7): size == 5");
    check(v[0]      == 7,        "assign: [0] == 7");
    check(v[4]      == 7,        "assign: [4] == 7");

    // assign меньшего размера
    v.assign(2, 0);
    check(v.size()  == 2,        "assign(2,0): size == 2");
    check(v[0]      == 0,        "assign: [0] == 0");

    // assign нуля
    v.assign(0, 1);
    check(v.empty(),             "assign(0): empty()");
}

// 
//  Vector — at / operator[] / front / back / data
// 
void test_access()
{
    group("Vector — at / operator[] / front / back / data");

    Vector<int> v = {10, 20, 30, 40};

    check(v[0]      == 10,       "operator[0] == 10");
    check(v[3]      == 40,       "operator[3] == 40");
    check(v.at(1)   == 20,       "at(1) == 20");
    check(v.front() == 10,       "front() == 10");
    check(v.back()  == 40,       "back() == 40");
    check(v.data()  == &v[0],    "data() указывает на первый элемент");

    // Запись через operator[]
    v[0] = 99;
    check(v[0]      == 99,       "operator[]: запись");

    // at() выбрасывает исключение
    bool threw = false;
    try { v.at(100); }
    catch (const std::out_of_range&) { threw = true; }
    check(threw,                 "at(100): бросает out_of_range");

    // const-версии
    const Vector<int> cv = {1, 2, 3};
    check(cv[1]      == 2,       "const operator[1] == 2");
    check(cv.at(0)   == 1,       "const at(0) == 1");
    check(cv.front() == 1,       "const front() == 1");
    check(cv.back()  == 3,       "const back() == 3");
}

// 
//  Vector — swap
// 
void test_swap()
{
    group("Vector — swap");

    Vector<int> a = {1, 2, 3};
    Vector<int> b = {10, 20};

    size_t sizA = a.size(), sizB = b.size();
    size_t capA = a.capacity(), capB = b.capacity();

    a.swap(b);

    check(a.size()  == sizB,     "swap: a.size() == старый b.size()");
    check(b.size()  == sizA,     "swap: b.size() == старый a.size()");
    check(a[0]      == 10,       "swap: a[0] == 10");
    check(a[1]      == 20,       "swap: a[1] == 20");
    check(b[0]      == 1,        "swap: b[0] == 1");
    check(b[2]      == 3,        "swap: b[2] == 3");
    check(a.capacity() == capB,  "swap: capacity тоже поменялся");
    check(b.capacity() == capA,  "swap: capacity тоже поменялся (b)");
}

// 
//  Vector — operator==
// 
void test_equality()
{
    group("Vector — operator==");

    Vector<int> a = {1, 2, 3};
    Vector<int> b = {1, 2, 3};
    Vector<int> c = {1, 2, 4};
    Vector<int> d = {1, 2};

    check(a == b,                "равные векторы: ==");
    check(!(a == c),             "разные значения: != ");
    check(!(a == d),             "разный размер: !=");
}

// 
//  Vector — Iterator
// 
void test_iterator()
{
    group("Vector — Iterator");

    Vector<int> v = {1, 2, 3, 4, 5};

    // Сумма через iterator
    int sum = 0;
    for (auto it = v.begin(); it != v.end(); ++it)
        sum += *it;
    check(sum == 15,             "iterator: сумма == 15");

    // Запись через iterator
    for (auto it = v.begin(); it != v.end(); ++it)
        *it *= 2;
    check(v[0] == 2 && v[4]==10,"iterator: запись (*it *= 2)");

    // Range-based for
    int sum2 = 0;
    for (int x : v) sum2 += x;
    check(sum2 == 30,            "range-for: сумма == 30");

    // begin == end на пустом
    Vector<int> empty;
    check(empty.begin() == empty.end(), "begin==end на пустом");

    // Постфиксный ++
    auto it = v.begin();
    auto it2 = it++;
    check(*it2 == 2,             "постфиксный ++: старое значение");
    check(*it  == 4,             "постфиксный ++: новое значение");

    // operator+ / operator-
    auto it3 = v.begin() + 3;
    check(*it3 == 8,             "iterator + 3: верное значение");
}

// 
//  Vector — ConstIterator
// 
void test_const_iterator()
{
    group("Vector — ConstIterator");

    const Vector<int> cv = {5, 10, 15};
    int sum = 0;
    for (auto it = cv.cbegin(); it != cv.cend(); ++it)
        sum += *it;
    check(sum == 30,             "cbegin/cend: сумма == 30");
    check(*cv.cbegin() == 5,     "cbegin: первый элемент");
}

// 
//  Vector — ReverseIterator
// 
void test_reverse_iterator()
{
    group("Vector — ReverseIterator");

    Vector<int> v = {1, 2, 3, 4, 5};

    // Обратный обход
    int arr[5]; int idx = 0;
    for (auto it = v.rbegin(); it != v.rend(); ++it)
        arr[idx++] = *it;

    check(arr[0] == 5,           "rbegin: первый == 5");
    check(arr[4] == 1,           "rend-1: последний == 1");

    // Сумма одинакова
    int sum = 0;
    for (auto it = v.rbegin(); it != v.rend(); ++it) sum += *it;
    check(sum == 15,             "reverse: сумма == 15");

    // Один элемент
    Vector<int> one = {42};
    check(*one.rbegin() == 42,   "rbegin одного элемента == 42");
}

// 
//  Pair — конструкторы и поля
// 
void test_pair_basic()
{
    group("Pair — конструкторы и поля");

    Pair<int, double> p(5, 3.14);
    check(p.first  == 5,         "Pair first == 5");
    check(p.second == 3.14,      "Pair second == 3.14");

    // Default ctor
    Pair<int, int> p2;
    check(p2.first  == 0,        "default ctor: first == 0");
    check(p2.second == 0,        "default ctor: second == 0");

    // make_pair
    auto mp = make_pair(10, 2.71);
    check(mp.first  == 10,       "make_pair: first == 10");
    check(mp.second == 2.71,     "make_pair: second == 2.71");

    // Оператор ==
    Pair<int,int> a(1,2), b(1,2), c(1,3);
    check(a == b,                "operator==: равные");
    check(!(a == c),             "operator!=: разные");
}

// 
//  Pair — копирование и присваивание
// 
void test_pair_copy()
{
    group("Pair — копирование и присваивание");

    Pair<int, int> p(3, 7);
    Pair<int, int> p2 = p;          // copy ctor
    check(p2.first  == 3,        "copy ctor: first");
    check(p2.second == 7,        "copy ctor: second");

    p2.first = 99;
    check(p.first   == 3,        "copy ctor: независимость (deep copy)");

    Pair<int, int> p3;
    p3 = p;                         // operator=
    check(p3.first  == 3,        "operator=: first");
    check(p3.second == 7,        "operator=: second");
}

// 
//  Pair — вложенный Pair<Pair<T,T>, Pair<T,T>>
// 
void test_pair_nested()
{
    group("Pair — вложенный Pair<Pair<T,T>, Pair<T,T>>");

    Pair< Pair<int,int>, Pair<int,int> > nested(
        Pair<int,int>(1, 2),
        Pair<int,int>(3, 4)
    );
    check(nested.first.first   == 1, "nested first.first == 1");
    check(nested.first.second  == 2, "nested first.second == 2");
    check(nested.second.first  == 3, "nested second.first == 3");
    check(nested.second.second == 4, "nested second.second == 4");

    // double вложенность
    using PP = Pair< Pair<double,double>, Pair<double,double> >;
    PP a;
    a.first  = Pair<double,double>(1.1, 2.2);
    a.second = Pair<double,double>(3.3, 4.4);
    check(a.first.first   == 1.1,  "nested double: first.first");
    check(a.second.second == 4.4,  "nested double: second.second");

    // Копирование вложенного
    auto b = a;
    b.first.first = 99.9;
    check(a.first.first == 1.1,    "nested copy: независимость");
}

// 
//  Pair<Vector<int>, Vector<Pair<int,double>>>
// 
void test_pair_complex()
{
    group("Pair<Vector<int>, Vector<Pair<int,double>>>");

    Pair< Vector<int>, Vector<Pair<int,double>> > c;

    for (int i = 0; i < 5; i++) c.first.push_back(i * 10);
    for (int i = 0; i < 4; i++) c.second.push_back(Pair<int,double>(i, i * 1.5));

    check(c.first.size()       == 5,    "first.size() == 5");
    check(c.first[2]           == 20,   "first[2] == 20");
    check(c.second.size()      == 4,    "second.size() == 4");
    check(c.second[3].first    == 3,    "second[3].first == 3");
    check(c.second[3].second   == 4.5,  "second[3].second == 4.5");

    // Копирование complex pair
    auto c2 = c;
    c2.first[0] = 999;
    check(c.first[0]           == 0,    "complex copy: deep copy first");
    c2.second[0].first = 777;
    check(c.second[0].first    == 0,    "complex copy: deep copy second");
}

// 
//  quickSort
// 
void test_quicksort()
{
    group("quickSort");

    auto isSorted = [](Vector<int>& v) {
        for (size_t i = 1; i < v.size(); i++)
            if (v[i] < v[i-1]) return false;
        return true;
    };

    // Обычный случай
    Vector<int> v = {5, 3, 8, 1, 9, 2, 7, 4, 6};
    quickSort(v, 0, (int)v.size()-1, [](const Vector<int>&){});
    check(isSorted(v),           "quickSort: обычный массив");
    check(v[0] == 1 && v[8]==9, "quickSort: min и max верны");

    // Уже отсортированный
    Vector<int> v2 = {1, 2, 3, 4, 5};
    quickSort(v2, 0, (int)v2.size()-1, [](const Vector<int>&){});
    check(isSorted(v2),          "quickSort: уже отсортирован");

    // Обратный порядок
    Vector<int> v3 = {5, 4, 3, 2, 1};
    quickSort(v3, 0, (int)v3.size()-1, [](const Vector<int>&){});
    check(isSorted(v3),          "quickSort: обратный порядок");

    // Одинаковые элементы
    Vector<int> v4 = {7, 7, 7, 7};
    quickSort(v4, 0, (int)v4.size()-1, [](const Vector<int>&){});
    check(isSorted(v4),          "quickSort: одинаковые элементы");

    // Один элемент
    Vector<int> v5 = {42};
    quickSort(v5, 0, 0, [](const Vector<int>&){});
    check(v5[0] == 42,           "quickSort: один элемент");

    // Два элемента
    Vector<int> v6 = {2, 1};
    quickSort(v6, 0, 1, [](const Vector<int>&){});
    check(v6[0]==1 && v6[1]==2, "quickSort: два элемента");

    // Отрицательные числа
    Vector<int> v7 = {-3, 5, -1, 0, 2};
    quickSort(v7, 0, (int)v7.size()-1, [](const Vector<int>&){});
    check(isSorted(v7),          "quickSort: с отрицательными");
    check(v7[0] == -3,           "quickSort: минимум == -3");

    // Callback вызывается
    int callCount = 0;
    Vector<int> v8 = {3, 1, 2};
    quickSort(v8, 0, (int)v8.size()-1, [&](const Vector<int>&){ callCount++; });
    check(callCount > 0,         "quickSort: callback вызывался");
}

// 
//  binarySearch
// 
void test_binary_search()
{
    group("binarySearch");

    Vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    check(binarySearch(v, 1)  == 0,  "найти первый элемент");
    check(binarySearch(v, 10) == 9,  "найти последний элемент");
    check(binarySearch(v, 5)  == 4,  "найти средний элемент");
    check(binarySearch(v, 0)  == -1, "не найден (меньше min)");
    check(binarySearch(v, 11) == -1, "не найден (больше max)");
    check(binarySearch(v, 99) == -1, "не найден (произвольный)");

    // Один элемент
    Vector<int> one = {42};
    check(binarySearch(one, 42) == 0,   "один элемент: найден");
    check(binarySearch(one, 1)  == -1,  "один элемент: не найден");

    // Чётный размер
    Vector<int> even = {2, 4, 6, 8};
    check(binarySearch(even, 4) == 1,   "чётный массив: найден [1]");
    check(binarySearch(even, 8) == 3,   "чётный массив: найден [3]");
    check(binarySearch(even, 5) == -1,  "чётный массив: не найден");

    // Отрицательные числа
    Vector<int> neg = {-5, -3, -1, 0, 2};
    check(binarySearch(neg, -3) == 1,   "отрицательные: найден");
    check(binarySearch(neg, -4) == -1,  "отрицательные: не найден");
}

// 
//  Граничные случаи — разные типы
// 
void test_different_types()
{
    group("Vector с разными типами");

    // double
    Vector<double> vd;
    vd.push_back(1.1); vd.push_back(2.2); vd.push_back(3.3);
    check(vd.size() == 3,        "Vector<double>: size");
    check(vd[1]     == 2.2,      "Vector<double>: [1]");

    // string
    Vector<std::string> vs;
    vs.push_back("hello");
    vs.push_back("world");
    check(vs.size() == 2,        "Vector<string>: size");
    check(vs[0]     == "hello",  "Vector<string>: [0]");
    check(vs.front()== "hello",  "Vector<string>: front()");
    check(vs.back() == "world",  "Vector<string>: back()");

    // Pair внутри Vector
    Vector<Pair<int,int>> vp;
    vp.push_back(Pair<int,int>(1,2));
    vp.push_back(Pair<int,int>(3,4));
    check(vp.size()         == 2,    "Vector<Pair>: size");
    check(vp[0].first       == 1,    "Vector<Pair>[0].first");
    check(vp[1].second      == 4,    "Vector<Pair>[1].second");
}

// 
//  MAIN
// 
int main()
{
    std::cout << "═══════════════════════════════════════════\n";
    std::cout << "  Тесты: Vector, Pair, algorithms\n";
    std::cout << "═══════════════════════════════════════════\n";

    test_constructors();
    test_capacity_methods();
    test_reserve();
    test_resize();
    test_shrink_to_fit();
    test_push_emplace_back();
    test_pop_back();
    test_insert_emplace();
    test_erase();
    test_clear();
    test_assign();
    test_access();
    test_swap();
    test_equality();
    test_iterator();
    test_const_iterator();
    test_reverse_iterator();
    test_pair_basic();
    test_pair_copy();
    test_pair_nested();
    test_pair_complex();
    test_quicksort();
    test_binary_search();
    test_different_types();

    std::cout << "\n═══════════════════════════════════════════\n";
    std::cout << "  Итого:  " << total  << " тестов\n";
    std::cout << "  ✓ OK:   " << passed << "\n";
    if (failed > 0)
        std::cout << "  ✗ FAIL: " << failed << "\n";
    else
        std::cout << "  Все тесты пройдены!\n";
    std::cout << "═══════════════════════════════════════════\n";

    return failed > 0 ? 1 : 0;
}
