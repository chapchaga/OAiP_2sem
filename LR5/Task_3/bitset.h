#ifndef BITSET_H
#define BITSET_H

#include <vector>
#include <string>
#include <stdexcept>
#include <cstdint>

// BitSet class — stores N bits in chunks of 64 bits (uint64_t)
// Operations ~, &, | work in O(N/64), all others in O(1)
class BitSet {
public:
    explicit BitSet(size_t n = 64, unsigned long long val = 0ULL);
    BitSet(size_t n, unsigned long val);
    BitSet(size_t n, const std::string& str);
    BitSet(const BitSet&) = default;
    BitSet& operator=(const BitSet&) = default;

    // --- Element access ---
    bool operator[](size_t pos) const;
    // Non-const reference proxy for operator[]&
    class reference {
        BitSet& bs_;
        size_t  pos_;
    public:
        reference(BitSet& bs, size_t pos) : bs_(bs), pos_(pos) {}
        reference& operator=(bool val) { bs_.set_bit(pos_, val); return *this; }
        operator bool() const { return bs_.test(pos_); }
    };
    reference operator[](size_t pos);

    // --- Query ---
    bool   test(size_t pos) const;
    bool   all()  const;
    bool   any()  const;
    bool   none() const;
    size_t count() const;
    size_t size()  const { return N_; }

    // --- Modifiers ---
    BitSet& set();                   // all bits = 1
    BitSet& set(size_t pos, bool val = true);
    BitSet& reset();                 // all bits = 0
    BitSet& reset(size_t pos);
    BitSet& flip();                  // invert all
    BitSet& flip(size_t pos);

    // --- Conversions ---
    std::string        to_string()  const;
    unsigned long      to_ulong()   const;
    unsigned long long to_ullong()  const;

    // --- Bitwise operators (O(N/64)) ---
    BitSet  operator~()              const;
    BitSet& operator&=(const BitSet& rhs);
    BitSet& operator|=(const BitSet& rhs);
    BitSet& operator^=(const BitSet& rhs);

    friend BitSet operator&(BitSet lhs, const BitSet& rhs) { return lhs &= rhs; }
    friend BitSet operator|(BitSet lhs, const BitSet& rhs) { return lhs |= rhs; }
    friend BitSet operator^(BitSet lhs, const BitSet& rhs) { return lhs ^= rhs; }
    friend bool   operator==(const BitSet& a, const BitSet& b);
    friend bool   operator!=(const BitSet& a, const BitSet& b);

private:
    size_t N_;
    std::vector<uint64_t> data_; // data_[0] holds bits 0..63

    size_t   chunks()    const { return data_.size(); }
    size_t   chunk(size_t pos)  const { return pos >> 6; }
    uint64_t mask(size_t pos)   const { return uint64_t(1) << (pos & 63); }
    void     trim();             // zero out bits beyond N_
    void     check(size_t pos)  const;
    void     set_bit(size_t pos, bool val);
};

#endif // BITSET_H
