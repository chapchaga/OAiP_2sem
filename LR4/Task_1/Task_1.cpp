#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

// ================= HEAP SORT =================
void heapify(vector<int>& arr, int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr)
{
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// ================= QUICK SORT =================
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
        }
    }

    swap(arr[i + 1], arr[high]);
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

// ================= MERGE SORT =================
void merge(vector<int>& arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// ================= BINARY SEARCH =================
int binsearch(int* arr, int size, int digit)
{
    int left = 0, right = size - 1;

    while (left <= right)
    {
        int mid = (left + right) / 2;

        if (arr[mid] == digit)
            return mid;
        else if (arr[mid] < digit)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int main()
{
    int n;
    cout << "Введите размер массива: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Введите элементы:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    vector<int> a1 = arr, a2 = arr, a3 = arr;

    // Heap Sort
    auto start = chrono::high_resolution_clock::now();
    heapSort(a1);
    auto end = chrono::high_resolution_clock::now();
    cout << "Heap Sort time: "
         << chrono::duration<double, milli>(end - start).count()
         << " ms\n";

    // Quick Sort
    start = chrono::high_resolution_clock::now();
    quickSort(a2, 0, n - 1);
    end = chrono::high_resolution_clock::now();
    cout << "Quick Sort time: "
         << chrono::duration<double, milli>(end - start).count()
         << " ms\n";

    // Merge Sort
    start = chrono::high_resolution_clock::now();
    mergeSort(a3, 0, n - 1);
    end = chrono::high_resolution_clock::now();
    cout << "Merge Sort time: "
         << chrono::duration<double, milli>(end - start).count()
         << " ms\n";

    // Бинарный поиск (по отсортированному массиву)
    int digit;
    cout << "Введите число для поиска: ";
    cin >> digit;

    int index = binsearch(a2.data(), n, digit);
    cout << "Индекс: " << index << endl;

    return 0;
}
