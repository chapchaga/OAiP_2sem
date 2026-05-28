#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// функция медианы из 3 элементов
int median3(int a, int b, int c)
{
    vector<int> temp = {a, b, c};
    sort(temp.begin(), temp.end());
    return temp[1]; // средний элемент
}

int main()
{
    int n;
    cout << "Введите размер массива: ";
    cin >> n;

    vector<int> a(n);

    cout << "Введите элементы:\n";
    for (int i = 0; i < n; i++)
        cin >> a[i];

    vector<int> b;

    for (int i = 0; i < n; i += 3)
    {
        if (i + 2 < n)
        {
            // полная тройка
            b.push_back(median3(a[i], a[i + 1], a[i + 2]));
        }
        else
        {
            // неполная группа
            int sum = 0;
            int count = 0;

            for (int j = i; j < n; j++)
            {
                sum += a[j];
                count++;
            }

            b.push_back(sum / count); // среднее
        }
    }

    cout << "\nРезультат (массив b):\n";
    for (int x : b)
        cout << x << " ";

    cout << endl;

    return 0;
}