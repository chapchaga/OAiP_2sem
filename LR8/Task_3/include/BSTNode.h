#pragma once
#include <memory>

template<typename KeyType, typename ValueType>
struct BSTNode {
    std::pair<const KeyType, ValueType> data;
    std::shared_ptr<BSTNode> left;
    std::shared_ptr<BSTNode> right;
    std::weak_ptr<BSTNode> parent;

    std::shared_ptr<BSTNode> prev;
    std::shared_ptr<BSTNode> next;

    explicit BSTNode(const KeyType& key, const ValueType& val = ValueType{})
        : data(key, val), left(nullptr), right(nullptr) {}
};
