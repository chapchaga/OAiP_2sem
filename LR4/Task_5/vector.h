#pragma once
#include <stdexcept>
#include <initializer_list>

template<typename T>
class Vector
{
private:
    T*     data_;
    size_t size_;
    size_t capacity_;

    void reallocate(size_t new_cap)
    {
        T* new_data = new T[new_cap];
        for (size_t i = 0; i < size_; i++)
            new_data[i] = data_[i];
        delete[] data_;
        data_     = new_data;
        capacity_ = new_cap;
    }

public:
    // ===== КОНСТРУКТОРЫ =====
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    Vector(size_t n, const T& val = T()) : data_(nullptr), size_(0), capacity_(0)
    {
        assign(n, val);
    }

    Vector(std::initializer_list<T> il) : data_(nullptr), size_(0), capacity_(0)
    {
        reserve(il.size());
        for (const T& v : il) push_back(v);
    }

    // Копирующий конструктор
    Vector(const Vector& other) : data_(nullptr), size_(0), capacity_(0)
    {
        reserve(other.size_);
        for (size_t i = 0; i < other.size_; i++)
            push_back(other.data_[i]);
    }

    // Оператор копирующего присваивания
    Vector& operator=(const Vector& other)
    {
        if (this != &other)
        {
            clear();
            reserve(other.size_);
            for (size_t i = 0; i < other.size_; i++)
                push_back(other.data_[i]);
        }
        return *this;
    }

    // ===== ДЕСТРУКТОР =====
    ~Vector() { delete[] data_; }

    // ===== SIZE / CAPACITY =====
    size_t size()     const { return size_; }
    size_t capacity() const { return capacity_; }
    bool   empty()    const { return size_ == 0; }

    size_t max_size() const { return size_t(-1) / sizeof(T); }

    // ===== RESERVE =====
    void reserve(size_t new_cap)
    {
        if (new_cap > capacity_)
            reallocate(new_cap);
    }

    // ===== RESIZE =====
    void resize(size_t new_size, const T& val = T())
    {
        if (new_size > capacity_)
            reallocate(new_size);

        // Заполняем новые элементы значением val
        for (size_t i = size_; i < new_size; i++)
            data_[i] = val;

        size_ = new_size;
    }

    // ===== SHRINK TO FIT =====
    void shrink_to_fit()
    {
        if (size_ < capacity_)
            reallocate(size_ == 0 ? 1 : size_);
    }

    // ===== PUSH BACK =====
    void push_back(const T& value)
    {
        if (size_ == capacity_)
        {
            size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate(new_cap);
        }
        data_[size_++] = value;
    }

    // ===== EMPLACE BACK =====
    template<typename... Args>
    void emplace_back(Args&&... args)
    {
        if (size_ == capacity_)
        {
            size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate(new_cap);
        }
        data_[size_++] = T(args...);
    }

    // ===== POP BACK =====
    void pop_back()
    {
        if (size_ > 0) size_--;
    }

    // ===== INSERT =====
    void insert(size_t pos, const T& value)
    {
        if (pos > size_) return;

        if (size_ == capacity_)
        {
            size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate(new_cap);
        }

        for (size_t i = size_; i > pos; i--)
            data_[i] = data_[i - 1];

        data_[pos] = value;
        size_++;
    }

    // ===== EMPLACE =====
    template<typename... Args>
    void emplace(size_t pos, Args&&... args)
    {
        if (pos > size_) return;

        if (size_ == capacity_)
        {
            size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate(new_cap);
        }

        for (size_t i = size_; i > pos; i--)
            data_[i] = data_[i - 1];

        data_[pos] = T(args...);
        size_++;
    }

    // ===== ERASE =====
    void erase(size_t pos)
    {
        if (pos >= size_) return;

        for (size_t i = pos; i < size_ - 1; i++)
            data_[i] = data_[i + 1];

        size_--;
    }

    // ===== CLEAR =====
    void clear() { size_ = 0; }

    // ===== ASSIGN =====
    void assign(size_t count, const T& value)
    {
        clear();
        reserve(count);
        for (size_t i = 0; i < count; i++)
            push_back(value);
    }

    // ===== AT =====
    T& at(size_t index)
    {
        if (index >= size_)
            throw std::out_of_range("Index out of range");
        return data_[index];
    }

    const T& at(size_t index) const
    {
        if (index >= size_)
            throw std::out_of_range("Index out of range");
        return data_[index];
    }

    // ===== OPERATOR [] =====
    T&       operator[](size_t index)       { return data_[index]; }
    const T& operator[](size_t index) const { return data_[index]; }

    // ===== FRONT / BACK =====
    T& front() { return data_[0]; }
    T& back()  { return data_[size_ - 1]; }

    const T& front() const { return data_[0]; }
    const T& back()  const { return data_[size_ - 1]; }

    // ===== DATA =====
    T*       data()       { return data_; }
    const T* data() const { return data_; }

    // ===== SWAP =====
    void swap(Vector& other)
    {
        T*     tmp_data = data_;     data_     = other.data_;     other.data_     = tmp_data;
        size_t tmp_size = size_;     size_     = other.size_;     other.size_     = tmp_size;
        size_t tmp_cap  = capacity_; capacity_ = other.capacity_; other.capacity_ = tmp_cap;
    }

    // ===== ОПЕРАТОР СРАВНЕНИЯ =====
    bool operator==(const Vector& other) const
    {
        if (size_ != other.size_) return false;
        for (size_t i = 0; i < size_; i++)
            if (data_[i] != other.data_[i]) return false;
        return true;
    }

    // ===== ITERATOR =====
    class Iterator
    {
        T* ptr_;
    public:
        explicit Iterator(T* ptr) : ptr_(ptr) {}

        T& operator*()  { return *ptr_; }
        T* operator->() { return ptr_; }

        Iterator& operator++()   { ptr_++; return *this; }
        Iterator  operator++(int){ Iterator tmp = *this; ptr_++; return tmp; }
        Iterator& operator--()   { ptr_--; return *this; }

        Iterator operator+(int n) const { return Iterator(ptr_ + n); }
        Iterator operator-(int n) const { return Iterator(ptr_ - n); }

        bool operator!=(const Iterator& o) const { return ptr_ != o.ptr_; }
        bool operator==(const Iterator& o) const { return ptr_ == o.ptr_; }
        bool operator< (const Iterator& o) const { return ptr_ <  o.ptr_; }
    };

    // ===== CONST ITERATOR =====
    class ConstIterator
    {
        const T* ptr_;
    public:
        explicit ConstIterator(const T* ptr) : ptr_(ptr) {}

        const T& operator*()  const { return *ptr_; }
        const T* operator->() const { return ptr_; }

        ConstIterator& operator++() { ptr_++; return *this; }
        ConstIterator& operator--() { ptr_--; return *this; }

        bool operator!=(const ConstIterator& o) const { return ptr_ != o.ptr_; }
        bool operator==(const ConstIterator& o) const { return ptr_ == o.ptr_; }
    };

    Iterator      begin()  { return Iterator(data_); }
    Iterator      end()    { return Iterator(data_ + size_); }
    ConstIterator cbegin() const { return ConstIterator(data_); }
    ConstIterator cend()   const { return ConstIterator(data_ + size_); }

    // ===== REVERSE ITERATOR =====
    class ReverseIterator
    {
        T* ptr_;
    public:
        explicit ReverseIterator(T* ptr) : ptr_(ptr) {}

        T& operator*()  { return *ptr_; }
        T* operator->() { return ptr_; }

        ReverseIterator& operator++() { ptr_--; return *this; }
        ReverseIterator& operator--() { ptr_++; return *this; }

        bool operator!=(const ReverseIterator& o) const { return ptr_ != o.ptr_; }
        bool operator==(const ReverseIterator& o) const { return ptr_ == o.ptr_; }
    };

    ReverseIterator rbegin() { return ReverseIterator(data_ + size_ - 1); }
    ReverseIterator rend()   { return ReverseIterator(data_ - 1); }
};
