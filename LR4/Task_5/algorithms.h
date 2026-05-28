#pragma once
#include "vector.h"
#include <functional>
#include <algorithm>

using Callback = std::function<void(const Vector<int>&)>;

// ===== PARTITION =====
inline int partition(Vector<int>& arr, int low, int high, Callback cb)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            std::swap(arr[i], arr[j]);
            cb(arr);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    cb(arr);

    return i + 1;
}

// ===== QUICK SORT =====
inline void quickSort(Vector<int>& arr, int low, int high, Callback cb)
{
    if (low < high)
    {
        int pi = partition(arr, low, high, cb);
        quickSort(arr, low, pi - 1, cb);
        quickSort(arr, pi + 1, high, cb);
    }
}

// ===== BINARY SEARCH =====
inline int binarySearch(Vector<int>& arr, int x)
{
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right)
    {
        int mid = (left + right) / 2;

        if (arr[mid] == x)
            return mid;
        else if (arr[mid] < x)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}
