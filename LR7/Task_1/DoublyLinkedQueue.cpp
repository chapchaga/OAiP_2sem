#include "DoublyLinkedQueue.h"

DoublyLinkedQueue::DoublyLinkedQueue() : head(nullptr), tail(nullptr), size_(0) {}

DoublyLinkedQueue::~DoublyLinkedQueue() {
    clear();
}

void DoublyLinkedQueue::pushBack(const std::string& val) {
    Node* node = new Node(val);
    if (!tail) {
        head = tail = node;
    } else {
        node->prev = tail;
        tail->next = node;
        tail = node;
    }
    ++size_;
}

void DoublyLinkedQueue::pushFront(const std::string& val) {
    Node* node = new Node(val);
    if (!head) {
        head = tail = node;
    } else {
        node->next = head;
        head->prev = node;
        head = node;
    }
    ++size_;
}

void DoublyLinkedQueue::popFront() {
    if (!head) throw std::underflow_error("Queue is empty");
    Node* tmp = head;
    head = head->next;
    if (head) head->prev = nullptr;
    else tail = nullptr;
    delete tmp;
    --size_;
}

void DoublyLinkedQueue::popBack() {
    if (!tail) throw std::underflow_error("Queue is empty");
    Node* tmp = tail;
    tail = tail->prev;
    if (tail) tail->next = nullptr;
    else head = nullptr;
    delete tmp;
    --size_;
}

void DoublyLinkedQueue::clear() {
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
    tail = nullptr;
    size_ = 0;
}

bool DoublyLinkedQueue::empty() const {
    return size_ == 0;
}

int DoublyLinkedQueue::size() const {
    return size_;
}

Node* DoublyLinkedQueue::getHead() const {
    return head;
}

Node* DoublyLinkedQueue::getTail() const {
    return tail;
}

Node* DoublyLinkedQueue::nodeAt(int index) const {
    if (index < 0 || index >= size_) throw std::out_of_range("Index out of range");
    Node* cur = head;
    for (int i = 0; i < index; ++i) cur = cur->next;
    return cur;
}

void DoublyLinkedQueue::moveBlock(int startLine, int endLine, int targetPos) {
    if (startLine < 1 || endLine > size_ || startLine > endLine)
        throw std::invalid_argument("Invalid line range");
    if (targetPos < 0 || targetPos > size_)
        throw std::invalid_argument("Invalid target position");

    int s = startLine - 1;
    int e = endLine - 1;

    Node* blockStart = nodeAt(s);
    Node* blockEnd   = nodeAt(e);

    Node* beforeBlock = blockStart->prev;
    Node* afterBlock  = blockEnd->next;

    if (beforeBlock) beforeBlock->next = afterBlock;
    else head = afterBlock;

    if (afterBlock) afterBlock->prev = beforeBlock;
    else tail = beforeBlock;

    blockStart->prev = nullptr;
    blockEnd->next   = nullptr;

    int blockLen = endLine - startLine + 1;
    int adjustedTarget = targetPos;
    if (targetPos > endLine) adjustedTarget -= blockLen;
    if (targetPos > s) adjustedTarget = targetPos - blockLen;

    size_ -= blockLen;

    if (adjustedTarget <= 0) {
        blockEnd->next = head;
        if (head) head->prev = blockEnd;
        else tail = blockEnd;
        head = blockStart;
        blockStart->prev = nullptr;
    } else if (adjustedTarget >= size_) {
        blockStart->prev = tail;
        if (tail) tail->next = blockStart;
        else head = blockStart;
        tail = blockEnd;
        blockEnd->next = nullptr;
    } else {
        Node* insertAfter = nodeAt(adjustedTarget - 1);
        Node* insertBefore = insertAfter->next;

        insertAfter->next = blockStart;
        blockStart->prev = insertAfter;

        blockEnd->next = insertBefore;
        if (insertBefore) insertBefore->prev = blockEnd;
        else tail = blockEnd;
    }

    size_ += blockLen;
}
