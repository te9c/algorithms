#include <bits/stdc++.h>

template<uint64_t modT>
struct mint {
    static_assert(modT > 0);
    uint64_t number;

    mint() : number(0) {}

    template<typename T, std::enable_if_t<std::is_signed_v<T>, int64_t> = 0>
    mint(T val) {
        int64_t temp = static_cast<int64_t>(val);
        if (temp < 0) {
            temp += mod();
        }
        if (temp < 0) {
            temp %= mod();
            temp += mod();
        }
        number = temp;
        normalize();
    }
    
    template<typename T, std::enable_if_t<!std::is_signed_v<T>, int64_t> = 0>
    mint(T val) {
        number = static_cast<uint64_t>(val);
        normalize();
    }

    mint(const mint& other) = default;
    mint(mint&& other) = default;
    mint& operator=(const mint& other) = default;
    mint& operator=(mint&& other) = default;

    constexpr uint64_t mod() const {
        return modT;
    }

    void normalize() {
        if (number >= mod()) {
            number %= mod();
            if (number < 0) {
                number += mod();
            }
        }
    }

    mint pow(uint64_t n) {
        uint64_t res = 1;
        uint64_t a = number;
        while (n) {
            if (n & 1)
                res = (res * a) % mod();
            a = (a * a) % mod();
            n >>= 1;
        }
        return res;
    }

    static constexpr bool is_prime(uint64_t val) {
#ifdef LOCAL
        for (uint64_t i = 2; i * i <= val; ++i) {
            if (val % i == 0)
                return false;
        }
#endif
        return true;
    }
    mint inverse() {
        static_assert(is_prime(modT));
        assert(number != 0);
        return this->pow(mod() - 2);
    }

    mint operator+(const mint& other) const {
        if (number + other.number >= mod()) {
            return mint(number + other.number - mod());
        }
        return mint(number + other.number);
    }
    mint operator-(const mint& other) const {
        if (number < other.number) {
            return mint(number + mod() - other.number);
        }
        return mint(number - other.number);
    }
    mint operator*(const mint& other) const { return mint(number * other.number); }
    mint operator%(const mint& other) const { return mint(number % other.number); }
    mint& operator+=(const mint& other) {
        number += other.number;
        if (number >= mod()) {
            number -= mod();
        }
        return *this;
    }
    mint& operator-=(const mint& other) {
        if (number < other.number) {
            number += mod();
        }
        number -= other.number;
        return *this;
    }
    mint& operator*=(const mint& other) {
        number *= other.number;
        normalize();
        return *this;
    }
    mint& operator++() { ++number; if (number == mod()) number = 0; return *this; }
    mint operator++(int) const { mint tmp = *this; ++(*this); return tmp; }
    mint& operator--() { if (number == 0) number = mod(); --number; return *this; }
    mint operator--(int) { mint tmp = *this; --(*this); return tmp; }
    mint operator-() const {
        return mint(-number);
    }

    template<typename U>
    operator U() const {
        return static_cast<U>(number);
    }

    bool operator==(const mint& other) const { return number == other.number; }
    bool operator!=(const mint& other) const { return number != other.number; }
    bool operator<(const mint& other) const { return number < other.number; }
    bool operator<=(const mint& other) const { return number <= other.number; }
    bool operator>=(const mint& other) const { return number >= other.number; }
    bool operator>(const mint& other) const { return number > other.number; }

    friend std::ostream& operator<<(std::ostream& o, const mint& num) {
        return o << num.number;
    }
    friend std::istream& operator>>(std::istream& i, mint& num) {
        i >> num.number;
        num.normalize();
        return i;
    }
};

template<uint64_t T, typename U> bool operator==(const mint<T>& lhs, U rhs) { return lhs == mint<T>(rhs); }
template<uint64_t T, typename U> bool operator==(U lhs, const mint<T>& rhs) { return rhs == lhs; }
template<uint64_t T, typename U> bool operator!=(const mint<T>& lhs, U rhs) { return !(lhs == rhs); }
template<uint64_t T, typename U> bool operator!=(U lhs, const mint<T>& rhs) { return !(lhs == rhs); }
template<uint64_t T, typename U> bool operator<(const mint<T>& lhs, U rhs) { return lhs < mint<T>(rhs); }
template<uint64_t T, typename U> bool operator<(U lhs, const mint<T>& rhs) { return mint<T>(lhs) < rhs; }
template<uint64_t T, typename U> bool operator>(const mint<T>& lhs, U rhs) { return lhs > mint<T>(rhs); }
template<uint64_t T, typename U> bool operator>(U lhs, const mint<T>& rhs) { return mint<T>(lhs) > rhs; }
template<uint64_t T, typename U> bool operator<=(const mint<T>& lhs, U rhs) { return !(lhs > rhs); }
template<uint64_t T, typename U> bool operator<=(U lhs, const mint<T>& rhs) { return !(lhs > rhs); }
template<uint64_t T, typename U> bool operator>=(const mint<T>& lhs, U rhs) { return !(lhs < rhs); }
template<uint64_t T, typename U> bool operator>=(U lhs, const mint<T>& rhs) { return !(lhs < rhs); }

template <uint64_t T, typename U> mint<T> operator+(const mint<T>& lhs, U rhs) { return lhs + mint<T>(rhs); }
template <uint64_t T, typename U> mint<T> operator+(U lhs, const mint<T>& rhs) { return mint<T>(lhs) + rhs; }
template <uint64_t T, typename U> mint<T> operator-(const mint<T>& lhs, U rhs) { return lhs - mint<T>(rhs); }
template <uint64_t T, typename U> mint<T> operator-(U lhs, const mint<T>& rhs) { return mint<T>(lhs) - rhs; }
template <uint64_t T, typename U> mint<T> operator*(const mint<T>& lhs, U rhs) { return lhs * mint<T>(rhs); }
template <uint64_t T, typename U> mint<T> operator*(U lhs, const mint<T>& rhs) { return mint<T>(lhs) * rhs; }
template <uint64_t T, typename U> mint<T> operator%(const mint<T>& lhs, U rhs) { return mint<T>(lhs.number % rhs); }
template <uint64_t T, typename U> U operator%(U lhs, const mint<T>& rhs) { return lhs % rhs; }
