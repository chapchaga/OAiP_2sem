#include "ListHeap.h"
#include <queue>

std::shared_ptr<HeapNode> ListHeap::getNode(int index) const {
    if (!root_) return nullptr;
    std::vector<bool> path;
    int i = index;
    while (i > 0) {
        path.push_back(i % 2 == 0);
        i = (i - 1) / 2;
    }
    auto cur = root_;
    for (int j = static_cast<int>(path.size()) - 1; j >= 0; --j) {
        if (!cur) return nullptr;
        cur = path[j] ? cur->right : cur->left;
    }
    return cur;
}

void ListHeap::siftUp(std::shared_ptr<HeapNode> node) {
    while (node) {
        auto par = node->parent.lock();
        if (!par) break;
        if (par->value < node->value) {
            std::swap(par->value, node->value);
            node = par;
        } else break;
    }
}

void ListHeap::siftDown(std::shared_ptr<HeapNode> node) {
    while (node) {
        auto largest = node;
        if (node->left  && node->left->value  > largest->value) largest = node->left;
        if (node->right && node->right->value > largest->value) largest = node->right;
        if (largest == node) break;
        std::swap(node->value, largest->value);
        node = largest;
    }
}

void ListHeap::insert(int value) {
    auto newNode = std::make_shared<HeapNode>(value);
    if (!root_) {
        root_ = newNode;
        size_ = 1;
        return;
    }
    int idx = size_;
    size_++;
    int parentIdx = (idx - 1) / 2;
    auto par = getNode(parentIdx);
    newNode->parent = par;
    if (!par->left) par->left = newNode;
    else            par->right = newNode;
    siftUp(newNode);
}

void ListHeap::extractMax() {
    if (!root_) throw std::runtime_error("Heap is empty");
    if (size_ == 1) {
        root_.reset();
        size_ = 0;
        return;
    }
    auto last = getNode(size_ - 1);
    root_->value = last->value;
    auto par = last->parent.lock();
    if (par) {
        if (par->right == last) par->right.reset();
        else                    par->left.reset();
    }
    size_--;
    siftDown(root_);
}

int ListHeap::getMax() const {
    if (!root_) throw std::runtime_error("Heap is empty");
    return root_->value;
}

bool ListHeap::isEmpty() const {
    return root_ == nullptr;
}

void ListHeap::clear() {
    root_.reset();
    size_ = 0;
}

std::vector<int> ListHeap::levelOrder() const {
    std::vector<int> result;
    if (!root_) return result;
    std::queue<std::shared_ptr<HeapNode>> q;
    q.push(root_);
    while (!q.empty()) {
        auto node = q.front(); q.pop();
        result.push_back(node->value);
        if (node->left)  q.push(node->left);
        if (node->right) q.push(node->right);
    }
    return result;
}
