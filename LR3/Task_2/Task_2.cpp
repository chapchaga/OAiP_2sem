#include <iostream>
#include <limits>

using namespace std;

// Рекурсивная функция Аккермана
unsigned long long ackermann(unsigned int m, unsigned int n) {
    if (m == 0)
        return n + 1;
    if (n == 0)
        return ackermann(m - 1, 1);

    return ackermann(m - 1, ackermann(m, n - 1));
}

int main() {
    setlocale(LC_ALL, "Russian");

    unsigned int m, n;

    cout << "Вычисление функции Аккермана A(m, n)\n";
    cout << "A(m, n) определяется так:\n";
    cout << "1) A(0, n) = n + 1\n";
    cout << "2) A(m, 0) = A(m - 1, 1), если m > 0\n";
    cout << "3) A(m, n) = A(m - 1, A(m, n - 1)), если m > 0 и n > 0\n\n";

    cout << "Введите m: ";
    while (!(cin >> m)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка ввода. Введите целое неотрицательное число для m: ";
    }

    cout << "Введите n: ";
    while (!(cin >> n)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка ввода. Введите целое неотрицательное число для n: ";
    }

    // Предупреждение: функция Аккермана очень быстро растёт
    if (m > 3 || (m == 3 && n > 10)) {
        cout << "\nПредупреждение: для таких значений функция Аккермана "
             << "может вычисляться очень долго или привести к переполнению стека.\n";
    }

    try {
        unsigned long long result = ackermann(m, n);
        cout << "\nA(" << m << ", " << n << ") = " << result << endl;
    }
    catch (...) {
        cout << "Произошла ошибка при вычислении функции.\n";
    }

    return 0;
}