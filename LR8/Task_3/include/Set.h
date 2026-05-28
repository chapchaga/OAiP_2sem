#pragma once
#include "Map.h"

template<typename KeyType>
class Set : public Map<KeyType, char> {
public:
    using Base = Map<KeyType, char>;

    void insert(const KeyType& key) {
        Base::insert(key, '\0');
    }

    bool contains(const KeyType& key) const {
        return Base::contains(key);
    }

    void erase(const KeyType& key) {
        Base::erase(key);
    }

    std::vector<KeyType> toVector() const {
        std::vector<KeyType> res;
        auto pairs = Base::toVector();
        for (auto& p : pairs) res.push_back(p.first);
        return res;
    }
};
