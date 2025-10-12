#include <bits/stdc++.h>

using namespace std;

struct long_num {
    vector<int> num;
    const int base = 1000*1000*1000;

    long_num(long_num const &ln) {
        num = ln.num;
    }
    long_num(int n) {
        while (n > 0) {
            num.push_back(n % base);
            n/=base;
        }

        if (num.empty())
            num.push_back(0);
    }
    long_num(string s) {
        for (int i = (int)s.size(); i > 0; i-=9) {
            if (i >= 9) {
                num.push_back(atoi(s.substr(i-9, 9).c_str()));
            } else {
                num.push_back(atoi(s.substr(0, i).c_str()));
            }
        }
    }
    long_num() : long_num(0) {}

    string str() const {
        string res = to_string(num.back());
        for (int i = (int)num.size() - 2; i >= 0; --i) {
            res += string(9 - (int)to_string(num[i]).size(), '0') + to_string(num[i]);
        }
        return res;
    }

    friend ostream& operator<<(ostream& stream, const long_num& ln) {
        stream << ln.str();
        return stream;
    }

    long_num operator+(const long_num& other) const {
        long_num result;
        result.num.clear();

        int carry = 0;
        for (size_t i = 0; i < max(other.num.size(), num.size()); ++i) {
            int a = other.num.size() > i ? other.num[i] : 0;
            int b = num.size() > i ? num[i] : 0;

            result.num.push_back(a + b + carry);
            carry = 0;
            if (result.num.back() >= base) {
                result.num.back() -= base;
                carry = 1;
            }
        }
        if (carry) {
            result.num.push_back(1);
        }
        return result;
    }
    long_num operator*(const long_num& other) const {
        long_num res;
        res.num.assign(num.size() + other.num.size(), 0);

        for (size_t i = 0; i < num.size(); ++i) {
            for (int j = 0, carry = 0; j < (int)other.num.size() || carry; ++j) {
                long long cur = res.num[i + j] + num[i] * 1ll * (j < (int)other.num.size() ? other.num[j] : 0) + carry;
                res.num[i+j] = int(cur % base);
                carry = int(cur / base);

            }
        }

        while (res.num.size() > 1 && res.num.back() == 0) {
            res.num.pop_back();
        }

        return res;
    }
    void operator*=(const long_num& other) {
        *this = *this * other;
    }
    bool operator<(const long_num& other) const {
        if (num.size() < other.num.size()) {
            return true;
        }
        else if (num.size() > other.num.size()) {
            return false;
        }

        for (int i = (int)num.size() - 1; i >= 0; --i) {
            if (num[i] > other.num[i]) {
                return false;
            } else if (num[i] < other.num[i]) {
                return true;
            }
        }
        return false;
    }
    bool operator>(const long_num& other) const {
        if (num.size() < other.num.size()) {
            return false;
        }
        else if (num.size() > other.num.size()) {
            return true;
        }

        for (int i = (int)num.size() - 1; i >= 0; --i) {
            if (num[i] > other.num[i]) {
                return true;
            } else if (num[i] < other.num[i]) {
                return false;
            }
        }
        return false;
    }
    friend bool operator==(const long_num& n1, const long_num& n2) {
        if (n1.num.size() != n2.num.size()) {
            return false;
        }

        for (int i = 0; i < (int)n1.num.size(); ++i) {
            if (n1.num[i] != n2.num[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator<=(const long_num& other) const {
        return !(*this > other);
    }
    bool operator>=(const long_num& other) const {
        return !(*this < other);
    }
    long_num operator=(long_num other) {
        num = other.num;
        return *this;
    }
};

// driver
int main() {
    long_num a(0), b(0);
    std::cout << (a < b) << '\n';
}
