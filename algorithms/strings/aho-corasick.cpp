#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// <= 'z'
#define ALPHABET_SIZE 123

struct Aho {
    struct Node {
        Node* suffix_link = nullptr;
        Node* next[ALPHABET_SIZE] = {0};
        Node* parent = nullptr;
        Node* up = nullptr;

        char c;
        bool is_terminal = false;
    };

    Node* root = new Node();

    void add_to_trie(const string& s) {
        auto now = root;
        for (auto ch : s) {
            int c = ch; // there could be optimization
            if (now->next[c] == nullptr) {
                now->next[c] = new Node();
                now->next[c]->parent = now;
                now->next[c]->c = c;
            }
            now = now->next[c];
        }
        now->is_terminal = true;
    }

    void build() {
        queue<Node*> q;
        q.push(root);

        while (q.size()) {
            auto node = q.front();
            q.pop();

            if (node->parent != nullptr) {
                if (node->parent == root) {
                    node->suffix_link = root;
                } else {
                    node->suffix_link = node->parent->suffix_link->next[(int)node->c];
                }

                if (node->suffix_link != root) {
                    if (node->suffix_link->is_terminal) {
                        node->up = node->suffix_link;
                    } else {
                        node->up = node->suffix_link->up;
                    }
                }
            }
            for (int i = 0; i < ALPHABET_SIZE; ++i) {
                if (node->next[i] != nullptr) {
                    q.push(node->next[i]);
                    continue;
                }
                if (node == root) {
                    node->next[i] = root;
                } else {
                    node->next[i] = node->suffix_link->next[i];
                }
            }
        }
    }
};
