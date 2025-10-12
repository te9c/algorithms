#include <bits/stdc++.h>

template<uint64_t modT>
struct mint {
    const uint64_t modulo = modT;
    uint64_t number;

    mint(int64_t number = 0) {
        this->number = number;
        normalize();
    }

    void normalize() {
        if (number >= modulo) {
            number %= modulo;
        }
    }

    mint operator+(const mint& other) const {
        return mint(number + other.number);
    }
    mint operator-(const mint& other) const {
        if (number < other.number) {
            return mint(number + modulo - other.number);
        }
        return mint(number - other.number);
    }
    mint operator*(const mint& other) const {
        return mint(number * other);
    }
    mint& operator+=(const mint& other) {
        number += other.number;
        normalize();
        return *this;
    }
    mint& operator-=(const mint& other) {
        if (number < other.number) {
            number += modulo;
        }
        number -= other.number;
        return *this;
    }
    mint& operator*=(const mint& other) {
        number *= other;
        normalize();
        return number;
    }
    bool operator==(const mint& other) const { return number == other.number; }
    bool operator!=(const mint& other) const { return number != other.number; }
    bool operator<(const mint& other) const { return number < other.number; }
    bool operator<=(const mint& other) const { return number <= other.number; }
    bool operator>=(const mint& other) const { return number >= other.number; }
    bool operator>(const mint& other) const { return number > other.number; }
    operator bool () const { return number; }

    friend std::ostream& operator<<(std::ostream& o, const mint& num) {
        return o << num.number;
    }
    friend std::istream& operator>>(std::istream& i, mint& num) {
        i >> num.number;
        num.normalize();
        return i;
    }
};
