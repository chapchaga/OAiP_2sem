#pragma once
#include <vector>
#include <stdexcept>

class ArrayHeap {
public:
    void insert(int value);
    void extractMax();
    int getMax() const;
    bool isEmpty() const;
    const std::vector<int>& data() const;
    void clear();

private:
    std::vector<int> heap_;
    void siftUp(int idx);
    void siftDown(int idx);
};
