#ifndef MYSTRING_H
#define MYSTRING_H

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <iterator>

#ifdef STRINGLIB_LIBRARY
#  define STRINGLIB_EXPORT __attribute__((visibility("default")))
#else
#  define STRINGLIB_EXPORT
#endif

class STRINGLIB_EXPORT MyString
{
public:
    // ── Iterator ────────────────────────────────────────────────
    class iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = char;
        using difference_type   = std::ptrdiff_t;
        using pointer           = char*;
        using reference         = char&;

        explicit iterator(pointer p) : ptr_(p) {}

        reference  operator*()  const { return *ptr_; }
        pointer    operator->() const { return ptr_; }
        iterator&  operator++()       { ++ptr_; return *this; }
        iterator   operator++(int)    { iterator tmp = *this; ++ptr_; return tmp; }
        iterator&  operator--()       { --ptr_; return *this; }
        iterator   operator--(int)    { iterator tmp = *this; --ptr_; return tmp; }
        iterator   operator+(difference_type n) const { return iterator(ptr_ + n); }
        iterator   operator-(difference_type n) const { return iterator(ptr_ - n); }
        difference_type operator-(const iterator& o)  const { return ptr_ - o.ptr_; }
        bool operator==(const iterator& o) const { return ptr_ == o.ptr_; }
        bool operator!=(const iterator& o) const { return ptr_ != o.ptr_; }
        bool operator< (const iterator& o) const { return ptr_ <  o.ptr_; }

    private:
        pointer ptr_;
    };

    class const_iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = char;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const char*;
        using reference         = const char&;

        explicit const_iterator(pointer p) : ptr_(p) {}

        reference       operator*()  const { return *ptr_; }
        pointer         operator->() const { return ptr_; }
        const_iterator& operator++()       { ++ptr_; return *this; }
        const_iterator  operator++(int)    { const_iterator tmp=*this; ++ptr_; return tmp; }
        const_iterator& operator--()       { --ptr_; return *this; }
        const_iterator  operator--(int)    { const_iterator tmp=*this; --ptr_; return tmp; }
        const_iterator  operator+(difference_type n) const { return const_iterator(ptr_+n); }
        const_iterator  operator-(difference_type n) const { return const_iterator(ptr_-n); }
        difference_type operator-(const const_iterator& o) const { return ptr_ - o.ptr_; }
        bool operator==(const const_iterator& o) const { return ptr_ == o.ptr_; }
        bool operator!=(const const_iterator& o) const { return ptr_ != o.ptr_; }
        bool operator< (const const_iterator& o) const { return ptr_ <  o.ptr_; }

    private:
        pointer ptr_;
    };

    // ── Constructors / Rule of Three ─────────────────────────────
    MyString();                              // default
    explicit MyString(const char* s);        // from C-string
    MyString(size_t n, char c);              // n copies of c
    MyString(const MyString& other);         // copy constructor   [Rule of 3]
    MyString& operator=(const MyString& other); // copy assignment [Rule of 3]
    ~MyString();                             // destructor          [Rule of 3]

    // ── Iterators ────────────────────────────────────────────────
    iterator       begin()        { return iterator(data_.get()); }
    iterator       end()          { return iterator(data_.get() + size_); }
    const_iterator begin()  const { return const_iterator(data_.get()); }
    const_iterator end()    const { return const_iterator(data_.get() + size_); }
    const_iterator cbegin() const { return const_iterator(data_.get()); }
    const_iterator cend()   const { return const_iterator(data_.get() + size_); }

    // ── Capacity ─────────────────────────────────────────────────
    size_t size()     const { return size_; }
    size_t capacity() const { return capacity_; }
    bool   empty()    const { return size_ == 0; }
    void   reserve(size_t newCap);
    void   resize(size_t newSize, char fill = '\0');

    // ── Element access ───────────────────────────────────────────
    char& operator[](size_t i)       { return data_[i]; }
    char  operator[](size_t i) const { return data_[i]; }
    char& at(size_t i);
    char  at(size_t i) const;
    const char* c_str() const { return data_.get(); }
    char* data()              { return data_.get(); }
    const char* data() const  { return data_.get(); }

    // ── Comparison operators ──────────────────────────────────────
    bool operator==(const MyString& o) const;
    bool operator!=(const MyString& o) const;
    bool operator< (const MyString& o) const;
    bool operator<=(const MyString& o) const;
    bool operator> (const MyString& o) const;
    bool operator>=(const MyString& o) const;

    // ── Concatenation ─────────────────────────────────────────────
    MyString& operator+=(const MyString& o);
    MyString  operator+(const MyString& o) const;

    // ══════════════════════════════════════════════════════════════
    //  C-string / memory functions — static members
    //  All implemented from scratch (no <cstring> calls internally)
    // ══════════════════════════════════════════════════════════════

    // Memory
    static void*  Memcpy (void* s1, const void* s2, size_t n);
    static void*  Memmove(void* s1, const void* s2, size_t n);
    static int    Memcmp (const void* s1, const void* s2, size_t n);
    static void*  Memset (void* s, int c, size_t n);

    // String copy
    static char*  Strcpy (char* s1, const char* s2);
    static char*  Strncpy(char* s1, const char* s2, size_t n);

    // String concatenation
    static char*  Strcat (char* s1, const char* s2);
    static char*  Strncat(char* s1, const char* s2, size_t n);

    // String comparison
    static int    Strcmp  (const char* s1, const char* s2);
    static int    Strcoll (const char* s1, const char* s2);
    static int    Strncmp (const char* s1, const char* s2, size_t n);
    static size_t Strxfrm (char* s1, const char* s2, size_t n);

    // Tokenization
    static char*  Strtok  (char* s1, const char* s2);

    // Misc
    static char*  Strerror(int errnum);
    static size_t Strlen  (const char* s);

private:
    std::unique_ptr<char[]> data_;   // smart pointer — owns the buffer
    size_t size_;
    size_t capacity_;

    static char* strtok_state_;      // internal state for Strtok

    void ensureCapacity(size_t needed);
    void allocate(size_t cap);
};

extern "C"
{
STRINGLIB_EXPORT size_t ExportedStrlen(const char* str);
}

#endif // MYSTRING_H
