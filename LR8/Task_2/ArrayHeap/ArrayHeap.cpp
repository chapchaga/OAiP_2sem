#include "ArrayHeap.h"

void ArrayHeap::insert(int value) {
    heap_.push_back(value);
    siftUp(static_cast<int>(heap_.size()) - 1);
}

void ArrayHeap::extractMax() {
    if (heap_.empty()) throw std::runtime_error("Heap is empty");
    heap_[0] = heap_.back();
    heap_.pop_back();
    if (!heap_.empty()) siftDown(0);
}

int ArrayHeap::getMax() const {
    if (heap_.empty()) throw std::runtime_error("Heap is empty");
    return heap_[0];
}

bool ArrayHeap::isEmpty() const {
    return heap_.empty();
}

const std::vector<int>& ArrayHeap::data() const {
    return heap_;
}

void ArrayHeap::clear() {
    heap_.clear();
}

void ArrayHeap::siftUp(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap_[parent] < heap_[idx]) {
            std::swap(heap_[parent], heap_[idx]);
            idx = parent;
        } else break;
    }
}

void ArrayHeap::siftDown(int idx) {
    int n = static_cast<int>(heap_.size());
    while (true) {
        int largest = idx;
        int left  = 2 * idx + 1;
        int right = 2 * idx + 2;
        if (left  < n && heap_[left]  > heap_[largest]) largest = left;
        if (right < n && heap_[right] > heap_[largest]) largest = right;
        if (largest == idx) break;
        std::swap(heap_[idx], heap_[largest]);
        idx = largest;
    }
}
