#pragma once
#include "BSTNode.h"
#include <functional>
#include <stdexcept>
#include <vector>

template<typename KeyType, typename ValueType>
class Map {
public:
    using NodeType = BSTNode<KeyType, ValueType>;
    using NodePtr  = std::shared_ptr<NodeType>;

    class Iterator {
    public:
        explicit Iterator(NodePtr node, bool useLinked = false)
            : current_(node), useLinked_(useLinked) {}

        std::pair<const KeyType, ValueType>& operator*()  { return current_->data; }
        std::pair<const KeyType, ValueType>* operator->() { return &current_->data; }

        Iterator& operator++() {
            if (!current_) return *this;
            if (useLinked_) {
                current_ = current_->next;
            } else {
                current_ = treeNext(current_);
            }
            return *this;
        }

        bool operator==(const Iterator& o) const { return current_ == o.current_; }
        bool operator!=(const Iterator& o) const { return current_ != o.current_; }

    private:
        NodePtr current_;
        bool useLinked_;

        NodePtr treeNext(NodePtr node) {
            if (!node) return nullptr;
            if (node->right) {
                auto cur = node->right;
                while (cur->left) cur = cur->left;
                return cur;
            }
            auto p = node->parent.lock();
            while (p && node == p->right) {
                node = p;
                p = p->parent.lock();
            }
            return p;
        }
    };

    Map() = default;
    virtual ~Map() = default;

    void insert(const KeyType& key, const ValueType& value = ValueType{}) {
        root_ = insertNode(root_, nullptr, key, value);
        rebuildLinkedList();
    }

    bool contains(const KeyType& key) const {
        return findNode(root_, key) != nullptr;
    }

    void erase(const KeyType& key) {
        root_ = eraseNode(root_, key);
        rebuildLinkedList();
    }

    ValueType& operator[](const KeyType& key) {
        auto node = findNode(root_, key);
        if (!node) {
            insert(key);
            node = findNode(root_, key);
        }
        return node->data.second;
    }

    const ValueType& operator[](const KeyType& key) const {
        auto node = findNode(root_, key);
        if (!node) throw std::out_of_range("Key not found");
        return node->data.second;
    }

    Iterator begin(bool linked = false) const {
        if (!root_) return end(linked);
        if (linked) return Iterator(listHead_, true);
        auto cur = root_;
        while (cur->left) cur = cur->left;
        return Iterator(cur, false);
    }

    Iterator end(bool linked = false) const {
        return Iterator(nullptr, linked);
    }

    std::vector<std::pair<KeyType, ValueType>> toVector() const {
        std::vector<std::pair<KeyType, ValueType>> res;
        inorder(root_, res);
        return res;
    }

    void clear() {
        root_ = nullptr;
        listHead_ = nullptr;
    }

    bool empty() const { return root_ == nullptr; }

    NodePtr root() const { return root_; }

protected:
    NodePtr root_;
    NodePtr listHead_;

    NodePtr insertNode(NodePtr node, NodePtr parent, const KeyType& key, const ValueType& val) {
        if (!node) {
            auto n = std::make_shared<NodeType>(key, val);
            n->parent = parent;
            return n;
        }
        if (key < node->data.first) {
            node->left = insertNode(node->left, node, key, val);
        } else if (key > node->data.first) {
            node->right = insertNode(node->right, node, key, val);
        } else {
            node->data.second = val;
        }
        return node;
    }

    NodePtr findNode(NodePtr node, const KeyType& key) const {
        if (!node) return nullptr;
        if (key == node->data.first) return node;
        if (key < node->data.first) return findNode(node->left, key);
        return findNode(node->right, key);
    }

    NodePtr eraseNode(NodePtr node, const KeyType& key) {
        if (!node) return nullptr;
        if (key < node->data.first) {
            node->left = eraseNode(node->left, key);
        } else if (key > node->data.first) {
            node->right = eraseNode(node->right, key);
        } else {
            if (!node->left) return node->right;
            if (!node->right) return node->left;
            auto minNode = node->right;
            while (minNode->left) minNode = minNode->left;
            node->right = eraseNode(node->right, minNode->data.first);
            minNode->left = node->left;
            minNode->right = node->right;
            if (node->left)  node->left->parent  = minNode;
            if (node->right) node->right->parent = minNode;
            minNode->parent = node->parent;
            return minNode;
        }
        return node;
    }

    void rebuildLinkedList() {
        std::vector<NodePtr> nodes;
        collectNodes(root_, nodes);
        listHead_ = nullptr;
        for (int i = 0; i < (int)nodes.size(); ++i) {
            nodes[i]->prev = (i > 0) ? nodes[i-1] : nullptr;
            nodes[i]->next = (i + 1 < (int)nodes.size()) ? nodes[i+1] : nullptr;
        }
        if (!nodes.empty()) listHead_ = nodes[0];
    }

    void collectNodes(NodePtr node, std::vector<NodePtr>& out) const {
        if (!node) return;
        collectNodes(node->left, out);
        out.push_back(node);
        collectNodes(node->right, out);
    }

    void inorder(NodePtr node, std::vector<std::pair<KeyType,ValueType>>& out) const {
        if (!node) return;
        inorder(node->left, out);
        out.push_back({node->data.first, node->data.second});
        inorder(node->right, out);
    }
};
