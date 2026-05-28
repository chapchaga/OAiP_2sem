#include "bst.h"
#include <stdexcept>
#include <queue>

BST::BST() : root(nullptr) {}

BST::~BST() {
    destroyTree(root);
}

void BST::destroyTree(Node* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

void BST::add(int value) {
    Node* newNode = new Node(value);
    if (!root) {
        root = newNode;
        return;
    }
    Node* cur = root;
    while (true) {
        if (value < cur->value) {
            if (!cur->left) {
                cur->left = newNode;
                newNode->parent = cur;
                return;
            }
            cur = cur->left;
        } else if (value > cur->value) {
            if (!cur->right) {
                cur->right = newNode;
                newNode->parent = cur;
                return;
            }
            cur = cur->right;
        } else {
            delete newNode;
            return;
        }
    }
}

Node* BST::findMin(Node* node) const {
    while (node->left) node = node->left;
    return node;
}

Node* BST::findNode(Node* node, int value) const {
    if (!node) return nullptr;
    if (value == node->value) return node;
    if (value < node->value) return findNode(node->left, value);
    return findNode(node->right, value);
}

Node* BST::find(int value) const {
    return findNode(root, value);
}

Node* BST::removeNode(Node* node) {
    if (!node->left && !node->right) {
        if (node->parent) {
            if (node->parent->left == node) node->parent->left = nullptr;
            else node->parent->right = nullptr;
        } else {
            root = nullptr;
        }
        delete node;
        return nullptr;
    }
    if (!node->left || !node->right) {
        Node* child = node->left ? node->left : node->right;
        child->parent = node->parent;
        if (node->parent) {
            if (node->parent->left == node) node->parent->left = child;
            else node->parent->right = child;
        } else {
            root = child;
        }
        delete node;
        return child;
    }
    Node* successor = findMin(node->right);
    node->value = successor->value;
    removeNode(successor);
    return node;
}

bool BST::remove(int value) {
    Node* node = findNode(root, value);
    if (!node) return false;
    removeNode(node);
    return true;
}

void BST::inorder(Node* node, std::vector<int>& result) const {
    if (!node) return;
    inorder(node->left, result);
    result.push_back(node->value);
    inorder(node->right, result);
}

std::vector<int> BST::traverse() const {
    std::vector<int> result;
    inorder(root, result);
    return result;
}

void BST::copySubtree(Node*& dest, Node* src, Node* destParent) {
    if (!src) { dest = nullptr; return; }
    dest = new Node(src->value);
    dest->parent = destParent;
    copySubtree(dest->left, src->left, dest);
    copySubtree(dest->right, src->right, dest);
}

bool BST::insertSubtree(int parentValue, BST* subtree, bool asLeftChild) {
    if (!subtree || !subtree->root) return false;
    Node* parent = findNode(root, parentValue);
    if (!parent) return false;

    Node* newSubRoot = nullptr;
    copySubtree(newSubRoot, subtree->root, parent);

    if (asLeftChild) {
        destroyTree(parent->left);
        parent->left = newSubRoot;
    } else {
        destroyTree(parent->right);
        parent->right = newSubRoot;
    }
    return true;
}

BST* BST::removeSubtree(int rootValue) {
    Node* node = findNode(root, rootValue);
    if (!node) return nullptr;

    BST* detached = new BST();
    copySubtree(detached->root, node, nullptr);

    if (node->parent) {
        if (node->parent->left == node) node->parent->left = nullptr;
        else node->parent->right = nullptr;
    } else {
        root = nullptr;
    }
    destroyTree(node);
    return detached;
}

void BST::removeBranchHelper(Node* node) {
    if (!node) return;
    removeBranchHelper(node->left);
    removeBranchHelper(node->right);
    delete node;
}

bool BST::removeBranch(int value) {
    Node* node = findNode(root, value);
    if (!node) return false;

    if (node->parent) {
        if (node->parent->left == node) node->parent->left = nullptr;
        else node->parent->right = nullptr;
    } else {
        root = nullptr;
    }
    removeBranchHelper(node);
    return true;
}

bool BST::insertAt(int parentValue, int newValue, bool asLeftChild) {
    Node* parent = findNode(root, parentValue);
    if (!parent) return false;
    Node* newNode = new Node(newValue);
    newNode->parent = parent;
    if (asLeftChild) {
        destroyTree(parent->left);
        parent->left = newNode;
    } else {
        destroyTree(parent->right);
        parent->right = newNode;
    }
    return true;
}

bool BST::isAncestor(Node* node, Node* target) const {
    if (!node) return false;
    if (node == target) return true;
    return isAncestor(node->left, target) || isAncestor(node->right, target);
}

Node* BST::lcaHelper(Node* node, int a, int b) const {
    if (!node) return nullptr;
    if (node->value == a || node->value == b) return node;
    Node* left = lcaHelper(node->left, a, b);
    Node* right = lcaHelper(node->right, a, b);
    if (left && right) return node;
    return left ? left : right;
}

int BST::lowestCommonAncestor(int a, int b) const {
    if (!find(a) || !find(b)) throw std::invalid_argument("Node not found");
    Node* result = lcaHelper(root, a, b);
    if (!result) throw std::runtime_error("LCA not found");
    return result->value;
}
