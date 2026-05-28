#pragma once
#include <memory>
#include <vector>
#include <stdexcept>

struct HeapNode {
    int value;
    std::shared_ptr<HeapNode> left;
    std::shared_ptr<HeapNode> right;
    std::weak_ptr<HeapNode>   parent;

    explicit HeapNode(int v) : value(v) {}
};

class ListHeap {
public:
    void insert(int value);
    void extractMax();
    int getMax() const;
    bool isEmpty() const;
    void clear();
    std::vector<int> levelOrder() const;

private:
    std::shared_ptr<HeapNode> root_;
    int size_ = 0;

    std::shared_ptr<HeapNode> getNode(int index) const;
    void siftUp(std::shared_ptr<HeapNode> node);
    void siftDown(std::shared_ptr<HeapNode> node);
};
