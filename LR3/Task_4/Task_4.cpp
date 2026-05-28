#include <iostream>
using namespace std;

// Рекурсивная функция Ханойской башни
void hanoi(int n, char from, char to, char aux)
{
    if (n == 1)
    {
        cout << "Move disk 1 from " << from << " to " << to << endl;
        return;
    }

    // Переместить n-1 дисков на вспомогательный стержень
    hanoi(n - 1, from, aux, to);

    // Переместить самый большой диск
    cout << "Move disk " << n << " from " << from << " to " << to << endl;

    // Переместить n-1 дисков на конечный стержень
    hanoi(n - 1, aux, to, from);
}

int main()
{
    int n;

    cout << "Enter number of disks: ";
    cin >> n;

    cout << "\nSteps to solve Tower of Hanoi:\n";

    hanoi(n, 'A', 'C', 'B');

    return 0;
}