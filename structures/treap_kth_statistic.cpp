#include <bits/stdc++.h>

using namespace std;
using ll = long long;

mt19937 rnd;

struct Treap {
    struct Node {
        int value;
        int prio = rnd();
        size_t subTreeSize = 1;
        Node* left = nullptr;
        Node* right = nullptr;
    };
    static const int npos = INT_MAX;
    size_t sz = 0;
    Node* root = nullptr;

    inline size_t size() const { return sz; }
    inline void update_size(Node* node) {
        if (!node) return;
        node->subTreeSize = 1 + (node->left ? node->left->subTreeSize : 0) + (node->right ? node->right->subTreeSize : 0);
    }
    inline size_t get_left_sz(Node* node) {
        if (!node) return 0;
        return node->left ? node->left->subTreeSize : 0;
    }

    // left := nodes->value < value
    pair<Node*, Node*> split(Node* node, int value) {
        if (!node) return {nullptr, nullptr};
        if (node->value < value) {
            auto [tl, tr] = split(node->right, value);
            node->right = tl;
            update_size(node);
            return {node, tr};
        } else {
            auto [tl, tr] = split(node->left, value);
            node->left = tr;
            update_size(node);
            return {tl, node};
        }
    }
    Node* merge(Node* t1, Node* t2) {
        if (!t1) return t2;
        if (!t2) return t1;
        if (t1->prio > t2->prio) {
            t1->right = merge(t1->right, t2);
            update_size(t1);
            return t1;
        } else {
            t2->left = merge(t1, t2->left);
            update_size(t2);
            return t2;
        }
    }

    void insert(int value) {
        auto [t1, t2] = split(root, value);
        auto [t21, t22] = split(t2, value + 1);
        if (t21 == nullptr) {
            t21 = new Node();
            t21->value = value;
            ++sz;
        }
        root = merge(t1, merge(t21, t22));
    }
    void erase(int value) {
        auto [t1, t2] = split(root, value);
        auto [t21, t22] = split(t2, value + 1);
        if (t21 != nullptr)
            --sz;
        root = merge(t1, t22);
    }
    bool find(int value) {
        auto now = root;
        while (now != nullptr) {
            if (now->value == value) return true;
            if (value < now->value) now = now->left;
            else now = now->right;
        }
        return false;
    }
    int find_by_order(size_t k) {
        auto now = root;
        while (now != nullptr) {
            size_t leftSubTree = get_left_sz(now);
            if (leftSubTree + 1 == k) return now->value;
            if (k < leftSubTree + 1) now = now->left;
            else {
                k -= leftSubTree + 1;
                now = now->right;
            }
        }
        return npos;
    }
    size_t order_of_key(int value) {
        auto now = root;
        size_t res = 0;
        while (now != nullptr) {
            if (now->value == value) {
                return res + get_left_sz(now) + 1;
            }
            if (value < now->value) now = now->left;
            else {
                res += get_left_sz(now) + 1;
                now = now->right;
            };
        }
        return res;
    }
};
