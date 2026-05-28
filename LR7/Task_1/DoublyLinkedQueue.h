#pragma once
#include <string>
#include <stdexcept>

struct Node {
    std::string data;
    Node* prev;
    Node* next;
    Node(const std::string& val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedQueue {
private:
    Node* head;
    Node* tail;
    int size_;

public:
    DoublyLinkedQueue();
    ~DoublyLinkedQueue();

    void pushBack(const std::string& val);
    void pushFront(const std::string& val);
    void popFront();
    void popBack();
    void clear();

    bool empty() const;
    int size() const;

    Node* getHead() const;
    Node* getTail() const;

    void moveBlock(int startLine, int endLine, int targetPos);

    Node* nodeAt(int index) const;
};
