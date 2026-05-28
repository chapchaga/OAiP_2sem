#include "BinarySearchTree.h"
#include <queue>
#include <stdexcept>

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

BinarySearchTree::~BinarySearchTree() {
    destroyTree(root);
}

void BinarySearchTree::destroyTree(TreeNode* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

int BinarySearchTree::height(TreeNode* node) const {
    if (!node) return 0;
    int l = height(node->left);
    int r = height(node->right);
    return 1 + (l > r ? l : r);
}

int BinarySearchTree::balanceFactor(TreeNode* node) const {
    if (!node) return 0;
    return height(node->left) - height(node->right);
}

TreeNode* BinarySearchTree::rotateRight(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T = x->right;
    x->right = y;
    y->left = T;
    return x;
}

TreeNode* BinarySearchTree::rotateLeft(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T = y->left;
    y->left = x;
    x->right = T;
    return y;
}

TreeNode* BinarySearchTree::balance(TreeNode* node) {
    int bf = balanceFactor(node);
    if (bf > 1) {
        if (balanceFactor(node->left) < 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (bf < -1) {
        if (balanceFactor(node->right) > 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

TreeNode* BinarySearchTree::insert(TreeNode* node, const Book& b) {
    if (!node) return new TreeNode(b);
    if (b.key < node->data.key)
        node->left = insert(node->left, b);
    else if (b.key > node->data.key)
        node->right = insert(node->right, b);
    else
        node->data = b;
    return node;
}

void BinarySearchTree::insert(const Book& b) {
    root = insert(root, b);
}

TreeNode* BinarySearchTree::findMin(TreeNode* node) const {
    while (node->left) node = node->left;
    return node;
}

TreeNode* BinarySearchTree::remove(TreeNode* node, int key) {
    if (!node) return nullptr;
    if (key < node->data.key)
        node->left = remove(node->left, key);
    else if (key > node->data.key)
        node->right = remove(node->right, key);
    else {
        if (!node->left) {
            TreeNode* tmp = node->right;
            delete node;
            return tmp;
        }
        if (!node->right) {
            TreeNode* tmp = node->left;
            delete node;
            return tmp;
        }
        TreeNode* successor = findMin(node->right);
        node->data = successor->data;
        node->right = remove(node->right, successor->data.key);
    }
    return node;
}

void BinarySearchTree::remove(int key) {
    root = remove(root, key);
}

const Book* BinarySearchTree::find(int key) const {
    TreeNode* cur = root;
    while (cur) {
        if (key == cur->data.key) return &cur->data;
        cur = key < cur->data.key ? cur->left : cur->right;
    }
    return nullptr;
}

void BinarySearchTree::collectInOrder(TreeNode* node, std::vector<Book>& out) const {
    if (!node) return;
    collectInOrder(node->left, out);
    out.push_back(node->data);
    collectInOrder(node->right, out);
}

TreeNode* BinarySearchTree::buildBalanced(std::vector<Book>& sorted, int lo, int hi) {
    if (lo > hi) return nullptr;
    int mid = (lo + hi) / 2;
    TreeNode* node = new TreeNode(sorted[mid]);
    node->left  = buildBalanced(sorted, lo, mid - 1);
    node->right = buildBalanced(sorted, mid + 1, hi);
    return node;
}

void BinarySearchTree::balanceTree() {
    std::vector<Book> sorted;
    collectInOrder(root, sorted);
    destroyTree(root);
    root = buildBalanced(sorted, 0, (int)sorted.size() - 1);
}

void BinarySearchTree::clear() {
    destroyTree(root);
    root = nullptr;
}

void BinarySearchTree::traversePreOrder(std::function<void(const Book&)> visit) const {
    std::function<void(TreeNode*)> go = [&](TreeNode* n) {
        if (!n) return;
        visit(n->data);
        go(n->left);
        go(n->right);
    };
    go(root);
}

void BinarySearchTree::traverseInOrder(std::function<void(const Book&)> visit) const {
    std::function<void(TreeNode*)> go = [&](TreeNode* n) {
        if (!n) return;
        go(n->left);
        visit(n->data);
        go(n->right);
    };
    go(root);
}

void BinarySearchTree::traversePostOrder(std::function<void(const Book&)> visit) const {
    std::function<void(TreeNode*)> go = [&](TreeNode* n) {
        if (!n) return;
        go(n->left);
        go(n->right);
        visit(n->data);
    };
    go(root);
}

TreeNode* BinarySearchTree::getRoot() const {
    return root;
}

std::vector<int> LibraryTree::nodesPerLevel() const {
    std::vector<int> result;
    if (!root) return result;

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = (int)q.size();
        result.push_back(levelSize);
        for (int i = 0; i < levelSize; ++i) {
            TreeNode* cur = q.front(); q.pop();
            if (cur->left)  q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
    }
    return result;
}
