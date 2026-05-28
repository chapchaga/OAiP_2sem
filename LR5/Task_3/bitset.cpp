#include "bitset.h"
#include <stdexcept>
#include <sstream>
#include <climits>

// ──────────────────────────────────────────────
// Helpers
// ──────────────────────────────────────────────
void BitSet::check(size_t pos) const {
    if (pos >= N_) throw std::out_of_range("BitSet: index out of range");
}

void BitSet::trim() {
    // Zero bits that are past N_ in the last chunk
    if (N_ % 64 != 0) {
        uint64_t mask_last = (uint64_t(1) << (N_ % 64)) - 1;
        data_.back() &= mask_last;
    }
}

void BitSet::set_bit(size_t pos, bool val) {
    check(pos);
    if (val) data_[chunk(pos)] |=  mask(pos);
    else     data_[chunk(pos)] &= ~mask(pos);
}

// ──────────────────────────────────────────────
// Constructors
// ──────────────────────────────────────────────
BitSet::BitSet(size_t n, unsigned long long val)
    : N_(n), data_((n + 63) / 64, 0) {
    if (n == 0) return;
    data_[0] = val;
    trim();
}

BitSet::BitSet(size_t n, unsigned long val)
    : BitSet(n, static_cast<unsigned long long>(val)) {}

BitSet::BitSet(size_t n, const std::string& str)
    : N_(n), data_((n + 63) / 64, 0) {
    size_t len = std::min(str.size(), n);
    for (size_t i = 0; i < len; ++i) {
        // str[0] is MSB (position n-1)
        if (str[i] == '1') {
            size_t bit = n - 1 - i;
            data_[chunk(bit)] |= mask(bit);
        } else if (str[i] != '0') {
            throw std::invalid_argument("BitSet: invalid character in string");
        }
    }
}

// ──────────────────────────────────────────────
// Element access
// ──────────────────────────────────────────────
bool BitSet::operator[](size_t pos) const { return test(pos); }
BitSet::reference BitSet::operator[](size_t pos) {
    check(pos);
    return reference(*this, pos);
}

// ──────────────────────────────────────────────
// Query
// ──────────────────────────────────────────────
bool BitSet::test(size_t pos) const {
    check(pos);
    return (data_[chunk(pos)] & mask(pos)) != 0;
}

bool BitSet::all() const {
    for (size_t i = 0; i < data_.size(); ++i) {
        uint64_t expected = UINT64_MAX;
        if (i == data_.size() - 1 && N_ % 64 != 0)
            expected = (uint64_t(1) << (N_ % 64)) - 1;
        if (data_[i] != expected) return false;
    }
    return true;
}

bool BitSet::any() const {
    for (auto w : data_) if (w) return true;
    return false;
}

bool BitSet::none() const { return !any(); }

size_t BitSet::count() const {
    size_t c = 0;
    for (auto w : data_) c += __builtin_popcountll(w);
    return c;
}

// ──────────────────────────────────────────────
// Modifiers
// ──────────────────────────────────────────────
BitSet& BitSet::set() {
    for (auto& w : data_) w = UINT64_MAX;
    trim();
    return *this;
}

BitSet& BitSet::set(size_t pos, bool val) {
    set_bit(pos, val);
    return *this;
}

BitSet& BitSet::reset() {
    for (auto& w : data_) w = 0;
    return *this;
}

BitSet& BitSet::reset(size_t pos) {
    check(pos);
    data_[chunk(pos)] &= ~mask(pos);
    return *this;
}

BitSet& BitSet::flip() {
    for (auto& w : data_) w = ~w;
    trim();
    return *this;
}

BitSet& BitSet::flip(size_t pos) {
    check(pos);
    data_[chunk(pos)] ^= mask(pos);
    return *this;
}

// ──────────────────────────────────────────────
// Conversions
// ──────────────────────────────────────────────
std::string BitSet::to_string() const {
    std::string s(N_, '0');
    for (size_t i = 0; i < N_; ++i)
        if ((data_[chunk(i)] & mask(i)) != 0)
            s[N_ - 1 - i] = '1';
    return s;
}

unsigned long long BitSet::to_ullong() const {
    unsigned long long result = 0;
    for (size_t i = 0; i < data_.size() && i < sizeof(unsigned long long); ++i)
        result |= data_[i] << (i * 64); // only first chunk fits
    // Simplified: just return first chunk
    return data_.empty() ? 0 : data_[0];
}

unsigned long BitSet::to_ulong() const {
    unsigned long long v = to_ullong();
    if (v > ULONG_MAX) throw std::overflow_error("BitSet::to_ulong overflow");
    return static_cast<unsigned long>(v);
}

// ──────────────────────────────────────────────
// Bitwise operators  O(N/64)
// ──────────────────────────────────────────────
BitSet BitSet::operator~() const {
    BitSet result(*this);
    result.flip();
    return result;
}

BitSet& BitSet::operator&=(const BitSet& rhs) {
    if (N_ != rhs.N_) throw std::invalid_argument("BitSet sizes differ");
    for (size_t i = 0; i < data_.size(); ++i)
        data_[i] &= rhs.data_[i];
    return *this;
}

BitSet& BitSet::operator|=(const BitSet& rhs) {
    if (N_ != rhs.N_) throw std::invalid_argument("BitSet sizes differ");
    for (size_t i = 0; i < data_.size(); ++i)
        data_[i] |= rhs.data_[i];
    return *this;
}

BitSet& BitSet::operator^=(const BitSet& rhs) {
    if (N_ != rhs.N_) throw std::invalid_argument("BitSet sizes differ");
    for (size_t i = 0; i < data_.size(); ++i)
        data_[i] ^= rhs.data_[i];
    return *this;
}

bool operator==(const BitSet& a, const BitSet& b) {
    return a.N_ == b.N_ && a.data_ == b.data_;
}

bool operator!=(const BitSet& a, const BitSet& b) { return !(a == b); }
