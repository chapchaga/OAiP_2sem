#pragma once
#include <forward_list>
#include <vector>
#include <functional>
#include <stdexcept>
#include <utility>

template<typename KeyType, typename ValueType, typename Hasher = std::hash<KeyType>>
class HashTable {
public:
    using BucketList = std::forward_list<std::pair<const KeyType, ValueType>>;

    explicit HashTable(size_t capacity = 16, Hasher hasher = Hasher{})
        : buckets_(capacity), size_(0), hasher_(hasher) {}

    bool contains(const KeyType& key) const {
        auto& bucket = buckets_[bucketIndex(key)];
        for (auto& p : bucket)
            if (p.first == key) return true;
        return false;
    }

    void insert(const KeyType& key, const ValueType& value = ValueType{}) {
        if ((size_ + 1) > buckets_.size() * maxLoadFactor_) rehash(buckets_.size() * 2);
        auto& bucket = buckets_[bucketIndex(key)];
        for (auto& p : bucket) {
            if (p.first == key) { p.second = value; return; }
        }
        bucket.emplace_front(key, value);
        ++size_;
    }

    void erase(const KeyType& key) {
        auto& bucket = buckets_[bucketIndex(key)];
        bucket.remove_if([&](const std::pair<const KeyType, ValueType>& p){
            if (p.first == key) { --size_; return true; }
            return false;
        });
    }

    ValueType& operator[](const KeyType& key) {
        if (!contains(key)) insert(key);
        auto& bucket = buckets_[bucketIndex(key)];
        for (auto& p : bucket)
            if (p.first == key) return p.second;
        throw std::runtime_error("unreachable");
    }

    ValueType operator[](const KeyType& key) const {
        auto& bucket = buckets_[bucketIndex(key)];
        for (auto& p : bucket)
            if (p.first == key) return p.second;
        throw std::out_of_range("Key not found");
    }

    void clear() {
        for (auto& b : buckets_) b.clear();
        size_ = 0;
    }

    void rehash(size_t newCapacity) {
        std::vector<BucketList> newBuckets(newCapacity);
        for (auto& bucket : buckets_) {
            for (auto& p : bucket) {
                size_t idx = hasher_(p.first) % newCapacity;
                newBuckets[idx].emplace_front(p.first, p.second);
            }
        }
        buckets_ = std::move(newBuckets);
    }

    size_t size()     const { return size_; }
    size_t capacity() const { return buckets_.size(); }

    std::vector<std::pair<KeyType, ValueType>> toVector() const {
        std::vector<std::pair<KeyType, ValueType>> res;
        for (auto& bucket : buckets_)
            for (auto& p : bucket)
                res.push_back({p.first, p.second});
        return res;
    }

private:
    std::vector<BucketList> buckets_;
    size_t size_;
    Hasher hasher_;
    double maxLoadFactor_ = 0.75;

    size_t bucketIndex(const KeyType& key) const {
        return hasher_(key) % buckets_.size();
    }
};
