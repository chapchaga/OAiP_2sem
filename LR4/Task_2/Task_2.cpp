#include <iostream>
#include <vector>
using namespace std;

// ================= QUICK SORT С ВЫВОДОМ =================
void printArray(const vector<int>& arr)
{
    for (int x : arr) cout << x << " ";
    cout << endl;
}

int partition(vector<int>& arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
            printArray(arr); // вывод после шага
        }
    }

    swap(arr[i + 1], arr[high]);
    printArray(arr); // вывод после шага

    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ================= INTERPOLATION SEARCH =================
int interpolationSearch(int arr[], int n, int x)
{
    int low = 0, high = n - 1;

    while (low <= high && x >= arr[low] && x <= arr[high])
    {
        if (low == high)
        {
            if (arr[low] == x) return low;
            return -1;
        }

        int pos = low + ((double)(high - low) /
                        (arr[high] - arr[low])) * (x - arr[low]);

        if (arr[pos] == x)
            return pos;

        if (arr[pos] < x)
            low = pos + 1;
        else
            high = pos - 1;
    }

    return -1;
}

// ================= BINPOW =================
long long binpow(long long a, long long b, long long mod)
{
    long long res = 1;
    a %= mod;

    while (b > 0)
    {
        if (b & 1)
            res = (res * a) % mod;

        a = (a * a) % mod;
        b >>= 1;
    }

    return res;
}

// ================= MAIN =================
int main()
{
    int n;
    cout << "Введите размер массива: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Введите элементы:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    cout << "\nШаги сортировки:\n";
    quickSort(arr, 0, n - 1);

    cout << "\nОтсортированный массив:\n";
    printArray(arr);

    int x;
    cout << "Введите число для поиска: ";
    cin >> x;

    int index = interpolationSearch(arr.data(), n, x);

    cout << "Индекс: " << index << endl;

    int mod;
    cout << "Введите mod: ";
    cin >> mod;

    if (index != -1)
    {
        cout << "Результат: "
             << binpow(index, n, mod)
             << endl;
    }
    else
    {
        cout << "Число не найдено\n";
    }

    return 0;
}