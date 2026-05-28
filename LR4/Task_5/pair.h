#pragma once
#include <ostream>

template<typename T1, typename T2>
struct Pair
{
    T1 first;
    T2 second;

    Pair() : first(T1()), second(T2()) {}
    Pair(const T1& f, const T2& s) : first(f), second(s) {}

    Pair(const Pair& other) : first(other.first), second(other.second) {}

    Pair& operator=(const Pair& other)
    {
        if (this != &other) { first = other.first; second = other.second; }
        return *this;
    }

    bool operator==(const Pair& other) const
    {
        return first == other.first && second == other.second;
    }

    bool operator!=(const Pair& other) const { return !(*this == other); }
};

template<typename T1, typename T2>
Pair<T1, T2> make_pair(const T1& a, const T2& b)
{
    return Pair<T1, T2>(a, b);
}

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const Pair<T1, T2>& p)
{
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
