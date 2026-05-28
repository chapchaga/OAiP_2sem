#pragma once
#include <stdexcept>
#include <cstddef>

template <typename T>
class MyDeque {
public:
    static const int BLOCK_SIZE = 4;

    struct Iterator {
        T** map;
        int mapSize;
        int blockIndex;
        int posInBlock;

        Iterator() : map(nullptr), mapSize(0), blockIndex(0), posInBlock(0) {}
        Iterator(T** m, int ms, int bi, int pi)
            : map(m), mapSize(ms), blockIndex(bi), posInBlock(pi) {}

        T& operator*() const {
            return map[blockIndex][posInBlock];
        }

        T* operator->() const {
            return &map[blockIndex][posInBlock];
        }

        Iterator& operator++() {
            posInBlock++;
            if (posInBlock == BLOCK_SIZE) {
                posInBlock = 0;
                blockIndex = (blockIndex + 1) % mapSize;
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator& operator--() {
            if (posInBlock == 0) {
                posInBlock = BLOCK_SIZE - 1;
                blockIndex = (blockIndex - 1 + mapSize) % mapSize;
            } else {
                posInBlock--;
            }
            return *this;
        }

        Iterator operator+(int n) const {
            Iterator it = *this;
            int total = blockIndex * BLOCK_SIZE + posInBlock + n;
            it.blockIndex = (total / BLOCK_SIZE) % mapSize;
            it.posInBlock = total % BLOCK_SIZE;
            if (it.posInBlock < 0) {
                it.posInBlock += BLOCK_SIZE;
                it.blockIndex = (it.blockIndex - 1 + mapSize) % mapSize;
            }
            return it;
        }

        bool operator==(const Iterator& o) const {
            return blockIndex == o.blockIndex && posInBlock == o.posInBlock;
        }

        bool operator!=(const Iterator& o) const {
            return !(*this == o);
        }
    };

private:
    T** map;
    int mapSize;
    int mapCap;

    int beginBlock, beginPos;
    int endBlock, endPos;
    int sz;

    void allocBlock(int idx) {
        map[idx] = new T[BLOCK_SIZE];
    }

    void freeBlock(int idx) {
        delete[] map[idx];
        map[idx] = nullptr;
    }

    void growMap() {
        int newCap = mapCap * 2;
        T** newMap = new T*[newCap]();

        int oldBeginBlock = beginBlock;
        int count = mapSize;

        int newStart = (newCap - count) / 2;
        for (int i = 0; i < count; i++) {
            newMap[newStart + i] = map[(oldBeginBlock + i) % mapSize];
        }

        for (int i = 0; i < newCap; i++) {
            if (newMap[i] == nullptr) {
                newMap[i] = new T[BLOCK_SIZE];
            }
        }

        int oldBeginBlock2 = beginBlock;
        int oldEndBlock = endBlock;
        (void)oldBeginBlock2;
        (void)oldEndBlock;

        int relBegin = 0;
        for (int i = 0; i < mapSize; i++) {
            if ((oldBeginBlock + i) % mapSize == beginBlock) { relBegin = i; break; }
        }
        int relEnd = 0;
        for (int i = 0; i < mapSize; i++) {
            if ((oldBeginBlock + i) % mapSize == endBlock) { relEnd = i; break; }
        }

        beginBlock = newStart + relBegin;
        endBlock = newStart + relEnd;

        delete[] map;
        map = newMap;
        mapSize = newCap;
        mapCap = newCap;
    }

public:
    MyDeque() : sz(0) {
        mapCap = 4;
        mapSize = 4;
        map = new T*[mapSize]();
        for (int i = 0; i < mapSize; i++) {
            map[i] = new T[BLOCK_SIZE];
        }
        beginBlock = mapSize / 2;
        beginPos = BLOCK_SIZE / 2;
        endBlock = beginBlock;
        endPos = beginPos;
    }

    ~MyDeque() {
        for (int i = 0; i < mapSize; i++) {
            delete[] map[i];
        }
        delete[] map;
    }

    MyDeque(const MyDeque&) = delete;
    MyDeque& operator=(const MyDeque&) = delete;

    int size() const { return sz; }
    bool empty() const { return sz == 0; }

    void clear() {
        for (int i = 0; i < mapSize; i++) {
            delete[] map[i];
        }
        delete[] map;
        mapCap = 4;
        mapSize = 4;
        map = new T*[mapSize]();
        for (int i = 0; i < mapSize; i++) {
            map[i] = new T[BLOCK_SIZE];
        }
        beginBlock = mapSize / 2;
        beginPos = BLOCK_SIZE / 2;
        endBlock = beginBlock;
        endPos = beginPos;
        sz = 0;
    }

    void push_back(const T& val) {
        map[endBlock][endPos] = val;
        sz++;
        endPos++;
        if (endPos == BLOCK_SIZE) {
            endPos = 0;
            endBlock = (endBlock + 1) % mapSize;
            if (endBlock == beginBlock && endPos == beginPos) {
                growMap();
            }
        }
    }

    void push_front(const T& val) {
        if (beginPos == 0) {
            beginPos = BLOCK_SIZE - 1;
            beginBlock = (beginBlock - 1 + mapSize) % mapSize;
        } else {
            beginPos--;
        }
        map[beginBlock][beginPos] = val;
        sz++;

        if (endBlock == beginBlock && endPos == beginPos) {
            push_back(val);
            pop_back();
            growMap();
        }
    }

    void pop_back() {
        if (sz == 0) throw std::underflow_error("Deque is empty");
        if (endPos == 0) {
            endPos = BLOCK_SIZE - 1;
            endBlock = (endBlock - 1 + mapSize) % mapSize;
        } else {
            endPos--;
        }
        sz--;
    }

    void pop_front() {
        if (sz == 0) throw std::underflow_error("Deque is empty");
        endPos++;
        if (beginPos == BLOCK_SIZE) {
            beginPos = 0;
            beginBlock = (beginBlock + 1) % mapSize;
        } else {
            beginPos++;
            if (beginPos == BLOCK_SIZE) {
                beginPos = 0;
                beginBlock = (beginBlock + 1) % mapSize;
            }
        }
        sz--;
    }

    T& operator[](int idx) {
        if (idx < 0 || idx >= sz) throw std::out_of_range("Index out of range");
        int totalPos = beginBlock * BLOCK_SIZE + beginPos + idx;
        int block = (totalPos / BLOCK_SIZE) % mapSize;
        int pos = totalPos % BLOCK_SIZE;
        return map[block][pos];
    }

    const T& operator[](int idx) const {
        if (idx < 0 || idx >= sz) throw std::out_of_range("Index out of range");
        int totalPos = beginBlock * BLOCK_SIZE + beginPos + idx;
        int block = (totalPos / BLOCK_SIZE) % mapSize;
        int pos = totalPos % BLOCK_SIZE;
        return map[block][pos];
    }

    T& front() {
        if (sz == 0) throw std::underflow_error("Deque is empty");
        return map[beginBlock][beginPos];
    }

    T& back() {
        if (sz == 0) throw std::underflow_error("Deque is empty");
        int pos = endPos - 1;
        int block = endBlock;
        if (pos < 0) { pos = BLOCK_SIZE - 1; block = (block - 1 + mapSize) % mapSize; }
        return map[block][pos];
    }

    Iterator begin() {
        return Iterator(map, mapSize, beginBlock, beginPos);
    }

    Iterator end() {
        return Iterator(map, mapSize, endBlock, endPos);
    }
};
