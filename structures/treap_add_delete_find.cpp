#include <bits/stdc++.h>

using namespace std;
using ll = long long;

mt19937 rnd;

struct Treap {
    struct Node {
        int value;
        int prio = rnd();
        Node* left = nullptr;
        Node* right = nullptr;
    };
    Node* root = nullptr;

    // left := nodes->value < value
    pair<Node*, Node*> split(Node* node, int value) {
        if (!node) return {nullptr, nullptr};
        if (node->value < value) {
            auto [tl, tr] = split(node->right, value);
            node->right = tl;
            return {node, tr};
        } else {
            auto [tl, tr] = split(node->left, value);
            node->left = tr;
            return {tl, node};
        }
    }

    Node* merge(Node* t1, Node* t2) {
        if (!t1) return t2;
        if (!t2) return t1;
        if (t1->prio > t2->prio) {
            t1->right = merge(t1->right, t2);
            return t1;
        } else {
            t2->left = merge(t1, t2->left);
            return t2;
        }
    }

    void insert(int value) {
        auto [t1, t2] = split(root, value);
        auto [t21, t22] = split(t2, value + 1);
        if (t21 == nullptr) {
            t21 = new Node();
            t21->value = value;
        }
        root = merge(t1, merge(t21, t22));
    }
    void erase(int value) {
        auto [t1, t2] = split(root, value);
        auto [t21, t22] = split(t2, value + 1);
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
};
