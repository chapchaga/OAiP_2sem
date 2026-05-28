#pragma once
#include <string>
#include <vector>
#include <functional>

struct Node {
    int value;
    Node* left;
    Node* right;
    Node* parent;

    Node(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BST {
public:
    BST();
    ~BST();

    void add(int value);
    bool remove(int value);
    Node* find(int value) const;
    std::vector<int> traverse() const;

    bool insertSubtree(int parentValue, BST* subtree, bool asLeftChild);
    BST* removeSubtree(int rootValue);

    bool removeBranch(int value);

    bool insertAt(int parentValue, int newValue, bool asLeftChild);

    int lowestCommonAncestor(int a, int b) const;

    Node* getRoot() const { return root; }

private:
    Node* root;

    void destroyTree(Node* node);
    Node* removeNode(Node* node);
    Node* findMin(Node* node) const;
    Node* findNode(Node* node, int value) const;
    void inorder(Node* node, std::vector<int>& result) const;
    bool isAncestor(Node* node, Node* target) const;
    Node* lcaHelper(Node* node, int a, int b) const;
    void copySubtree(Node*& dest, Node* src, Node* destParent);
    void removeBranchHelper(Node* node);
};
