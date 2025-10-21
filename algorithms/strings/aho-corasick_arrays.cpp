#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define MAX_NODES 1000
#define ALPHABET_SIZE 123

struct Aho {
    struct Node {
        int suffix_link = 0;
        int next[ALPHABET_SIZE];
        int parent = 0;
        int up = 0;

        char c;
        bool is_terminal = false;

        Node() {

        }
    };
    Node nodes[MAX_NODES];
    int sz = 2;

    int root = 1;

    void add_to_trie(const string& s) {
        int now = root;
        for (auto ch : s) {
            int c = ch;
            if (nodes[now].next[c] == -1) {
                int i = sz++;
                nodes[now].next[c] = i;
                nodes[i].parent = now;
                nodes[i].c = ch;
            }
            now = nodes[now].next[c];
        }
        nodes[now].is_terminal = true;
    }

    void build() {
        queue<int> q;
        q.push(root);

        while (q.size()) {
            auto node = q.front();
            q.pop();

            if (nodes[node].parent != 0) {
                if (nodes[node].parent == root) {
                    nodes[node].suffix_link = root;
                } else {
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
