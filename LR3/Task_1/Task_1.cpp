#include <iostream>
using namespace std;

// Рекурсивная функция перевода в двоичную систему
void toBinary(int n)
{
    if (n > 1)
    {
        toBinary(n / 2);  // рекурсивный вызов
    }
    cout << n % 2;        // вывод остатка
}

int main()
{
    int num;

    cout << "Введите десятичное число: ";
    cin >> num;

    cout << "Двоичное представление: ";
    toBinary(num);

    cout << endl;
    return 0;
}