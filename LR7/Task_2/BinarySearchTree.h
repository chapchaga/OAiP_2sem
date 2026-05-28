#pragma once
#include <string>
#include <vector>
#include <functional>

struct Book {
    int key;
    std::string author;
    std::string title;
    int year;
    std::string language;
};

struct TreeNode {
    Book data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(const Book& b) : data(b), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
protected:
    TreeNode* root;

private:
    TreeNode* insert(TreeNode* node, const Book& b);
    TreeNode* remove(TreeNode* node, int key);
    TreeNode* findMin(TreeNode* node) const;
    TreeNode* balance(TreeNode* node);
    TreeNode* buildBalanced(std::vector<Book>& sorted, int lo, int hi);
    void collectInOrder(TreeNode* node, std::vector<Book>& out) const;
    void destroyTree(TreeNode* node);
    int height(TreeNode* node) const;
    int balanceFactor(TreeNode* node) const;
    TreeNode* rotateRight(TreeNode* node);
    TreeNode* rotateLeft(TreeNode* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();

    void insert(const Book& b);
    void remove(int key);
    const Book* find(int key) const;
    void balanceTree();
    void clear();

    void traversePreOrder(std::function<void(const Book&)> visit) const;
    void traverseInOrder(std::function<void(const Book&)> visit) const;
    void traversePostOrder(std::function<void(const Book&)> visit) const;

    TreeNode* getRoot() const;
};

class LibraryTree : public BinarySearchTree {
public:
    std::vector<int> nodesPerLevel() const;
};
