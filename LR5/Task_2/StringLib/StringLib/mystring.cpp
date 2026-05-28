#include "mystring.h"
#include <stdexcept>
#include <cstring>   // only for ::strcoll, ::strxfrm, ::strerror
#include "mystring.h"

// ── Static member ───────────────────────────────────────────────
char* MyString::strtok_state_ = nullptr;

// ── Internal: check if char is in delimiter set ──────────────────
static bool inDelimiters(char c, const char* delims)
{
    for (size_t i = 0; delims[i] != '\0'; ++i)
        if (delims[i] == c) return true;
    return false;
}

// ══════════════════════════════════════════════════════════════
//  Private helpers
// ══════════════════════════════════════════════════════════════

void MyString::allocate(size_t cap)
{
    data_ = std::make_unique<char[]>(cap + 1);
    capacity_ = cap;
}

void MyString::ensureCapacity(size_t needed)
{
    if (needed <= capacity_) return;
    size_t newCap = (capacity_ == 0) ? 16 : capacity_ * 2;
    if (newCap < needed) newCap = needed;

    auto newData = std::make_unique<char[]>(newCap + 1);
    Memcpy(newData.get(), data_.get(), size_);
    newData[size_] = '\0';

    data_     = std::move(newData);
    capacity_ = newCap;
}

// ══════════════════════════════════════════════════════════════
//  Constructors / Rule of Three
// ══════════════════════════════════════════════════════════════

MyString::MyString() : size_(0), capacity_(0)
{
    allocate(0);
    data_[0] = '\0';
}

MyString::MyString(const char* s) : size_(0), capacity_(0)
{
    size_t len = Strlen(s);
    allocate(len);
    Memcpy(data_.get(), s, len);
    data_[len] = '\0';
    size_ = len;
}

MyString::MyString(size_t n, char c) : size_(0), capacity_(0)
{
    allocate(n);
    Memset(data_.get(), static_cast<unsigned char>(c), n);
    data_[n] = '\0';
    size_ = n;
}

// ── Copy constructor  [Rule of 3] ────────────────────────────────
MyString::MyString(const MyString& other) : size_(0), capacity_(0)
{
    allocate(other.size_);
    Memcpy(data_.get(), other.data_.get(), other.size_);
    data_[other.size_] = '\0';
    size_ = other.size_;
}

// ── Copy assignment  [Rule of 3] ─────────────────────────────────
MyString& MyString::operator=(const MyString& other)
{
    if (this == &other) return *this;          // self-assignment guard

    auto newData = std::make_unique<char[]>(other.size_ + 1);
    Memcpy(newData.get(), other.data_.get(), other.size_);
    newData[other.size_] = '\0';

    data_     = std::move(newData);
    size_     = other.size_;
    capacity_ = other.size_;
    return *this;
}

// ── Destructor  [Rule of 3] ──────────────────────────────────────
MyString::~MyString()
{
    // unique_ptr<char[]> calls delete[] automatically — nothing to do
}

// ══════════════════════════════════════════════════════════════
//  Capacity
// ══════════════════════════════════════════════════════════════

void MyString::reserve(size_t newCap)
{
    if (newCap <= capacity_) return;
    auto newData = std::make_unique<char[]>(newCap + 1);
    Memcpy(newData.get(), data_.get(), size_);
    newData[size_] = '\0';
    data_     = std::move(newData);
    capacity_ = newCap;
}

void MyString::resize(size_t newSize, char fill)
{
    if (newSize > capacity_) reserve(newSize);
    if (newSize > size_)
        Memset(data_.get() + size_, static_cast<unsigned char>(fill), newSize - size_);
    size_ = newSize;
    data_[size_] = '\0';
}

// ══════════════════════════════════════════════════════════════
//  Element access
// ══════════════════════════════════════════════════════════════

char& MyString::at(size_t i)
{
    if (i >= size_) throw std::out_of_range("MyString::at — index out of range");
    return data_[i];
}

char MyString::at(size_t i) const
{
    if (i >= size_) throw std::out_of_range("MyString::at — index out of range");
    return data_[i];
}

// ══════════════════════════════════════════════════════════════
//  Comparison operators
// ══════════════════════════════════════════════════════════════

bool MyString::operator==(const MyString& o) const
{
    if (size_ != o.size_) return false;
    return Memcmp(data_.get(), o.data_.get(), size_) == 0;
}
bool MyString::operator!=(const MyString& o) const { return !(*this == o); }
bool MyString::operator<(const MyString& o) const
{
    size_t minLen = (size_ < o.size_) ? size_ : o.size_;
    int r = Memcmp(data_.get(), o.data_.get(), minLen);
    if (r != 0) return r < 0;
    return size_ < o.size_;
}
bool MyString::operator<=(const MyString& o) const { return !(o < *this); }
bool MyString::operator>(const MyString& o)  const { return o < *this; }
bool MyString::operator>=(const MyString& o) const { return !(*this < o); }

// ══════════════════════════════════════════════════════════════
//  Concatenation
// ══════════════════════════════════════════════════════════════

MyString& MyString::operator+=(const MyString& o)
{
    ensureCapacity(size_ + o.size_);
    Memcpy(data_.get() + size_, o.data_.get(), o.size_);
    size_ += o.size_;
    data_[size_] = '\0';
    return *this;
}

MyString MyString::operator+(const MyString& o) const
{
    MyString result(*this);
    result += o;
    return result;
}

// ══════════════════════════════════════════════════════════════
//  STATIC C-FUNCTION IMPLEMENTATIONS  (no <cstring> calls)
// ══════════════════════════════════════════════════════════════

void* MyString::Memcpy(void* s1, const void* s2, size_t n)
{
    auto*       dst = static_cast<unsigned char*>(s1);
    const auto* src = static_cast<const unsigned char*>(s2);
    for (size_t i = 0; i < n; ++i) dst[i] = src[i];
    return s1;
}

void* MyString::Memmove(void* s1, const void* s2, size_t n)
{
    auto*       dst = static_cast<unsigned char*>(s1);
    const auto* src = static_cast<const unsigned char*>(s2);
    if (dst < src || dst >= src + n) {
        for (size_t i = 0;     i < n; ++i) dst[i]     = src[i];
    } else {
        for (size_t i = n; i > 0; --i) dst[i-1] = src[i-1];
    }
    return s1;
}

int MyString::Memcmp(const void* s1, const void* s2, size_t n)
{
    const auto* a = static_cast<const unsigned char*>(s1);
    const auto* b = static_cast<const unsigned char*>(s2);
    for (size_t i = 0; i < n; ++i) {
        if (a[i] < b[i]) return -1;
        if (a[i] > b[i]) return  1;
    }
    return 0;
}

void* MyString::Memset(void* s, int c, size_t n)
{
    auto* dst = static_cast<unsigned char*>(s);
    unsigned char val = static_cast<unsigned char>(c);
    for (size_t i = 0; i < n; ++i) dst[i] = val;
    return s;
}

size_t MyString::Strlen(const char* s)
{
    if (!s) return 0;
    size_t len = 0;
    while (s[len] != '\0') ++len;
    return len;
}

char* MyString::Strcpy(char* s1, const char* s2)
{
    char* dst = s1;
    while ((*dst++ = *s2++) != '\0') {}
    return s1;
}

char* MyString::Strncpy(char* s1, const char* s2, size_t n)
{
    size_t i = 0;
    for (; i < n && s2[i] != '\0'; ++i) s1[i] = s2[i];
    for (; i < n; ++i)                   s1[i] = '\0';
    return s1;
}

char* MyString::Strcat(char* s1, const char* s2)
{
    char* dst = s1 + Strlen(s1);
    while ((*dst++ = *s2++) != '\0') {}
    return s1;
}

char* MyString::Strncat(char* s1, const char* s2, size_t n)
{
    char* dst = s1 + Strlen(s1);
    size_t i  = 0;
    for (; i < n && s2[i] != '\0'; ++i) dst[i] = s2[i];
    dst[i] = '\0';
    return s1;
}

int MyString::Strcmp(const char* s1, const char* s2)
{
    const auto* a = reinterpret_cast<const unsigned char*>(s1);
    const auto* b = reinterpret_cast<const unsigned char*>(s2);
    while (*a && *a == *b) { ++a; ++b; }
    if (*a < *b) return -1;
    if (*a > *b) return  1;
    return 0;
}

int MyString::Strcoll(const char* s1, const char* s2)
{
    return ::strcoll(s1, s2);
}

int MyString::Strncmp(const char* s1, const char* s2, size_t n)
{
    const auto* a = reinterpret_cast<const unsigned char*>(s1);
    const auto* b = reinterpret_cast<const unsigned char*>(s2);
    for (size_t i = 0; i < n; ++i) {
        if (!a[i] && !b[i]) return 0;
        if (a[i] < b[i])    return -1;
        if (a[i] > b[i])    return  1;
    }
    return 0;
}

size_t MyString::Strxfrm(char* s1, const char* s2, size_t n)
{
    return ::strxfrm(s1, s2, n);
}

char* MyString::Strtok(char* s1, const char* s2)
{
    if (s1 != nullptr)
        strtok_state_ = s1;

    if (strtok_state_ == nullptr) return nullptr;

    // Skip leading delimiters
    while (*strtok_state_ && inDelimiters(*strtok_state_, s2))
        ++strtok_state_;

    if (*strtok_state_ == '\0') {
        strtok_state_ = nullptr;
        return nullptr;
    }

    char* tokenStart = strtok_state_;

    // Advance to next delimiter
    while (*strtok_state_ && !inDelimiters(*strtok_state_, s2))
        ++strtok_state_;

    if (*strtok_state_ != '\0') {
        *strtok_state_ = '\0';
        ++strtok_state_;
    } else {
        strtok_state_ = nullptr;
    }

    return tokenStart;
}

char* MyString::Strerror(int errnum)
{
    return ::strerror(errnum);
}

extern "C"
{
size_t ExportedStrlen(const char* str)
{
    return MyString::Strlen(str);
}
}
