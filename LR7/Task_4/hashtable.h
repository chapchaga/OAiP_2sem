#pragma once
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <cmath>

enum class SlotState { EMPTY, OCCUPIED, DELETED };

struct Slot {
    int key;
    std::string value;
    SlotState state;
    int probeCount;
    Slot() : key(0), value(""), state(SlotState::EMPTY), probeCount(0) {}
};

enum class HashType { MODULAR, UNIVERSAL };

class OpenHashTable {
public:
    int tableSize;
    std::vector<Slot> table;
    HashType hashType;
    int collisionCount;
    int elementCount;

    int p;
    int a;
    int b;

    OpenHashTable(int size, HashType type) 
        : tableSize(size), table(size), hashType(type),
          collisionCount(0), elementCount(0),
          p(1000003), a(0), b(0)
    {
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> distA(1, p - 1);
        std::uniform_int_distribution<int> distB(0, p - 1);
        a = distA(rng);
        b = distB(rng);
    }

    int modularHash(int key) const {
        return ((key % tableSize) + tableSize) % tableSize;
    }

    int universalHash(int key) const {
        long long k = (long long)key;
        long long h = ((long long)a * k + b) % p;
        if (h < 0) h += p;
        return (int)(h % tableSize);
    }

    int hashFunc(int key) const {
        if (hashType == HashType::MODULAR) return modularHash(key);
        return universalHash(key);
    }

    int probe(int h0, int i) const {
        return (h0 + i) % tableSize;
    }

    bool insert(int key, const std::string& val) {
        if (elementCount >= tableSize) return false;
        int h0 = hashFunc(key);
        int firstDeleted = -1;
        for (int i = 0; i < tableSize; i++) {
            int idx = probe(h0, i);
            if (table[idx].state == SlotState::EMPTY) {
                int dest = (firstDeleted >= 0) ? firstDeleted : idx;
                table[dest].key = key;
                table[dest].value = val;
                table[dest].state = SlotState::OCCUPIED;
                table[dest].probeCount = i;
                if (i > 0) collisionCount++;
                elementCount++;
                return true;
            } else if (table[idx].state == SlotState::DELETED) {
                if (firstDeleted < 0) firstDeleted = idx;
            } else {
                if (i > 0) {}
            }
        }
        if (firstDeleted >= 0) {
            table[firstDeleted].key = key;
            table[firstDeleted].value = val;
            table[firstDeleted].state = SlotState::OCCUPIED;
            table[firstDeleted].probeCount = tableSize;
            collisionCount++;
            elementCount++;
            return true;
        }
        return false;
    }

    long long searchTime(int key) const {
        auto start = std::chrono::high_resolution_clock::now();
        int h0 = hashFunc(key);
        for (int i = 0; i < tableSize; i++) {
            int idx = probe(h0, i);
            if (table[idx].state == SlotState::EMPTY) break;
            if (table[idx].state == SlotState::OCCUPIED && table[idx].key == key) break;
        }
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }

    long long searchBatch(const std::vector<int>& keys) const {
        long long total = 0;
        for (int k : keys) total += searchTime(k);
        return total;
    }

    void clear() {
        for (auto& s : table) s = Slot();
        collisionCount = 0;
        elementCount = 0;
    }

    double loadFactor() const {
        return (double)elementCount / tableSize;
    }

    std::string getDescription() const {
        return hashType == HashType::MODULAR
            ? "Modular: h(k) = k mod N"
            : "Universal: h(k) = ((a*k+b) mod p) mod N";
    }
};

struct BenchResult {
    int tableSize;
    long long timeModular;
    long long timeUniversal;
    int collisionsModular;
    int collisionsUniversal;
};

inline BenchResult runBenchmark(int size, int fillCount, const std::vector<int>& keys, const std::vector<std::string>& vals, const std::vector<int>& searchKeys) {
    OpenHashTable modTable(size, HashType::MODULAR);
    OpenHashTable uniTable(size, HashType::UNIVERSAL);

    int n = std::min(fillCount, size - 1);
    for (int i = 0; i < n; i++) {
        modTable.insert(keys[i], vals[i]);
        uniTable.insert(keys[i], vals[i]);
    }

    BenchResult r;
    r.tableSize = size;
    r.collisionsModular = modTable.collisionCount;
    r.collisionsUniversal = uniTable.collisionCount;
    r.timeModular = modTable.searchBatch(searchKeys);
    r.timeUniversal = uniTable.searchBatch(searchKeys);
    return r;
}
