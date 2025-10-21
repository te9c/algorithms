#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// get max
struct heap {
    vector<int> heapVec;

    int top() {
        return heapVec[0];
    }

    void sift_up(int index) {
        if (index == 0) return;

        int parent = (index - 1) / 2;
        if (heapVec[parent] < heapVec[index]) {
            swap(heapVec[parent], heapVec[index]);
            sift_up(parent);
        } else {
            return;
        }
    }

    void push(int value) {
        heapVec.push_back(value);
        sift_up((int)heapVec.size() - 1);
    }

    void sift_down(int index) {
        int left_child = index * 2 + 1;
        int right_child = index * 2 + 2;
        if (left_child >= (int)heapVec.size() && right_child >= (int)heapVec.size()) {
            return;
        }
        if (right_child >= (int)heapVec.size() || heapVec[left_child] > heapVec[right_child]) {
            if (heapVec[left_child] > heapVec[index]) {
                swap(heapVec[left_child], heapVec[index]);
                sift_down(left_child);
            }
        }
        else if (heapVec[right_child] > heapVec[index]) {
            swap(heapVec[right_child], heapVec[index]);
            sift_down(right_child);
        }
    }

    void pop() {
        swap(heapVec[0], heapVec.back());
        heapVec.pop_back();
        sift_down(0);
    }

    size_t size() {
        return heapVec.size();
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    heap a;
    a.push(5);
    a.push(753);
    a.push(31);
    a.push(151);
    a.push(1);
    a.push(537);
    a.push(15);
    a.push(115);

    while (a.size()) {
        std::cout << a.top() << '\n';
        a.pop();
    }

    return 0;
}
