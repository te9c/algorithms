#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct SuffAuto {
    struct Node {
        Node* link = nullptr;
        Node* parent = nullptr;
        Node* next[26] = {nullptr};
        int len = 0;
    };

    Node* root = new Node();
    Node* last = root;

    void addChar(char c) {
        Node* cur = new Node();
        Node* p = last;

        cur->link = root;
        cur->parent = p;
        cur->len = p->len + 1;

        while (p && p->next[c - 'a'] == nullptr) {
            p->next[c - 'a'] = cur;
            p = p->link;
        }

        if (p) {
            Node* q = p->next[c - 'a'];
            if (p->len + 1 == q->len) {
                cur->link = q;
            } else {
                Node* newc = new Node(*q);
                newc->len = p->len + 1;
                newc->parent = p;

                q->link = newc;
                cur->link = newc;

                while (p && p->next[c - 'a'] == q) {
                    p->next[c - 'a'] = newc;
                    p = p->link;
                }
            }
        }

        last = cur;
    }

    SuffAuto(const string& s = "") {
        for (auto c : s) {
            addChar(c);
        }
    }
};
