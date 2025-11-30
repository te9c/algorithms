#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define LEN 100

template<size_t L = LEN>
struct OrderedArray {
    vector<int> arr;
    int buffer[L];
    size_t buffer_size = 0;

    OrderedArray() {}
    OrderedArray(const vector<int>& a) {
        arr = a;
        sort(arr.begin(), arr.end());
    }
    void add(int value) {
        buffer[buffer_size++] = value;
        if (buffer_size == L) {
            recalc();
        }
    }
    void recalc() {
        sort(buffer, buffer + buffer_size);
        vector<int> newArr(buffer_size + arr.size());
        merge(arr.begin(), arr.end(), buffer, buffer + buffer_size, newArr.begin());
        arr = newArr;
        buffer_size = 0;
    }
    // in 1-index
    int order(int k) {
        --k;
        int idx = k;
    }
};
