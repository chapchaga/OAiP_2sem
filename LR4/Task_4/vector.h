#pragma once
#include <stdexcept>

template<typename T>
class Vector
{
private:
    T* data_;
    size_t size_;
    size_t capacity_;

    void reallocate(size_t new_cap)
    {
        T* new_data = new T[new_cap];

        for (size_t i = 0; i < size_; i++)
            new_data[i] = data_[i];

        delete[] data_;
        data_ = new_data;
        capacity_ = new_cap;
    }

public:
    // ===== КОНСТРУКТОР =====
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    // ===== ДЕСТРУКТОР =====
    ~Vector()
    {
        delete[] data_;
    }

    // ===== SIZE =====
    size_t size() const { return size_; }

    // ===== CAPACITY =====
    size_t capacity() const { return capacity_; }

    // ===== EMPTY =====
    bool empty() const { return size_ == 0; }

    // ===== RESERVE =====
    void reserve(size_t new_cap)
    {
        if (new_cap > capacity_)
            reallocate(new_cap);
    }

    // ===== RESIZE =====
    void resize(size_t new_size)
    {
        if (new_size > capacity_)
            reallocate(new_size);

        size_ = new_size;
    }

    // ===== MAX SIZE =====
    size_t max_size() const
    {
        return size_t(-1) / sizeof(T);
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
    void emplace_back(Args... args)
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
        if (size_ > 0)
            size_--;
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
    void emplace(size_t pos, Args... args)
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
    void clear()
    {
        size_ = 0;
    }

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

    // ===== OPERATOR [] =====
    T& operator[](size_t index)
    {
        return data_[index];
    }

    // ===== FRONT / BACK =====
    T& front() { return data_[0]; }
    T& back() { return data_[size_ - 1]; }

    // ===== DATA =====
    T* data() { return data_; }

    // ===== SWAP =====
    void swap(Vector& other)
    {
        T* tmp_data = data_;
        data_ = other.data_;
        other.data_ = tmp_data;

        size_t tmp_size = size_;
        size_ = other.size_;
        other.size_ = tmp_size;

        size_t tmp_cap = capacity_;
        capacity_ = other.capacity_;
        other.capacity_ = tmp_cap;
    }

    // ===== ITERATOR =====
    class Iterator
    {
        T* ptr_;
    public:
        Iterator(T* ptr) : ptr_(ptr) {}

        T& operator*() { return *ptr_; }

        Iterator& operator++()
        {
            ptr_++;
            return *this;
        }

        bool operator!=(const Iterator& other)
        {
            return ptr_ != other.ptr_;
        }
    };

    // ===== BEGIN / END =====
    Iterator begin() { return Iterator(data_); }
    Iterator end() { return Iterator(data_ + size_); }

    // ===== CONST ITERATOR =====
    Iterator cbegin() { return Iterator(data_); }

    // ===== REVERSE ITERATOR =====
    class ReverseIterator
    {
        T* ptr_;
    public:
        ReverseIterator(T* ptr) : ptr_(ptr) {}

        T& operator*() { return *ptr_; }

        ReverseIterator& operator++()
        {
            ptr_--;
            return *this;
        }

        bool operator!=(const ReverseIterator& other)
        {
            return ptr_ != other.ptr_;
        }
    };

    ReverseIterator rbegin() { return ReverseIterator(data_ + size_ - 1); }
    ReverseIterator rend() { return ReverseIterator(data_ - 1); }
};