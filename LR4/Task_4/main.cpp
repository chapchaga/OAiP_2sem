#include <iostream>
#include "vector.h"

using namespace std;

int main()
{
    Vector<int> v;

    // Добавление элементов
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    cout << "Vector: ";
    for (auto it = v.begin(); it != v.end(); ++it)
        cout << *it << " ";

    cout << endl;

    // Проверка методов
    cout << "Size: " << v.size() << endl;
    cout << "Capacity: " << v.capacity() << endl;
    cout << "Front: " << v.front() << endl;
    cout << "Back: " << v.back() << endl;

    // Удаление
    v.pop_back();

    cout << "After pop_back: ";
    for (auto it = v.begin(); it != v.end(); ++it)
        cout << *it << " ";

    cout << endl;

    return 0;
}
