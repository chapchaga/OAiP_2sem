#pragma once
#include <string>
#include <sstream>

struct StackNode {
    int key;
    std::string value;
    StackNode* next;
    StackNode(int k, const std::string& v) : key(k), value(v), next(nullptr) {}
};

class Stack {
public:
    StackNode* top;
    int count;
    Stack() : top(nullptr), count(0) {}
    ~Stack() { clear(); }
    void push(int key, const std::string& val) {
        StackNode* node = new StackNode(key, val);
        node->next = top;
        top = node;
        count++;
    }
    bool pop() {
        if (!top) return false;
        StackNode* tmp = top;
        top = top->next;
        delete tmp;
        count--;
        return true;
    }
    bool empty() const { return top == nullptr; }
    void clear() {
        while (pop());
    }
    std::string toString() const {
        std::ostringstream oss;
        StackNode* cur = top;
        while (cur) {
            oss << "[" << cur->key << ":" << cur->value << "]";
            if (cur->next) oss << "->";
            cur = cur->next;
        }
        return oss.str();
    }
};

class HashTable {
public:
    int tableSize;
    Stack* buckets;

    HashTable(int size) : tableSize(size) {
        buckets = new Stack[tableSize];
    }
    ~HashTable() { delete[] buckets; }

    int hashFunc(int key) const {
        return ((key % tableSize) + tableSize) % tableSize;
    }

    void insert(int key, const std::string& val) {
        int idx = hashFunc(key);
        buckets[idx].push(key, val);
    }

    bool remove(int key) {
        int idx = hashFunc(key);
        Stack& s = buckets[idx];
        if (s.empty()) return false;
        if (s.top->key == key) { s.pop(); return true; }
        StackNode* cur = s.top;
        while (cur->next) {
            if (cur->next->key == key) {
                StackNode* tmp = cur->next;
                cur->next = tmp->next;
                delete tmp;
                s.count--;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    StackNode* find(int key) const {
        int idx = hashFunc(key);
        StackNode* cur = buckets[idx].top;
        while (cur) {
            if (cur->key == key) return cur;
            cur = cur->next;
        }
        return nullptr;
    }

    void clear() {
        for (int i = 0; i < tableSize; i++) buckets[i].clear();
    }

    StackNode* findMax() const {
        StackNode* maxNode = nullptr;
        for (int i = 0; i < tableSize; i++) {
            StackNode* cur = buckets[i].top;
            while (cur) {
                if (!maxNode || cur->key > maxNode->key) maxNode = cur;
                cur = cur->next;
            }
        }
        return maxNode;
    }

    std::string toString() const {
        std::ostringstream oss;
        for (int i = 0; i < tableSize; i++) {
            oss << "Bucket " << i << ": ";
            if (buckets[i].empty()) oss << "(empty)";
            else oss << buckets[i].toString();
            oss << "\n";
        }
        return oss.str();
    }

    int totalCount() const {
        int c = 0;
        for (int i = 0; i < tableSize; i++) c += buckets[i].count;
        return c;
    }
};
