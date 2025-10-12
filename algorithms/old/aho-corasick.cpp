#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define ALPHABET_SIZE 26
const size_t sz = ALPHABET_SIZE + 1;

struct Node {
    Node* childs[sz];
    int c;
    Node* parent;
    Node* suffix_link;
    Node* next[sz];

    bool is_terminal;
    Node* up;

    Node() {
        c = ALPHABET_SIZE;
        parent = nullptr;
        suffix_link = nullptr;
        up = nullptr;
        is_terminal = false;
        for (size_t i = 0; i < sz; ++i) {
            childs[i] = nullptr;
            next[i] = nullptr;
        }
    }
};

// unordered_map<Node*, bool> get_terminal(Node* root, const vector<string>& patterns) {
//     unordered_map<Node*, bool> res;
//     for (const auto& pattern : patterns) {
//         auto now = root;
//         for (auto c : pattern) {
//             now = now->next[c - 'a'];
//         }
//         res[now] = true;
//     }
//
//     return res;
// }

Node* make_trie(const vector<string>& strs) {
    Node* root = new Node();
    root->is_terminal = true;

    for (const auto& str : strs) {
        Node* now = root;
        for (auto ch : str) {
            auto c = ch - 'a';

            if (now->childs[c] != nullptr) {
                now = now->childs[c];
            } else {
                Node* nd = new Node();
                nd->c = c;
                nd->parent = now;
                now->childs[c] = nd;
                now->next[c] = nd;
                now = nd;
            }
        }
        now->is_terminal = true;
    }

    return root;
}

void make_auto(Node* root) {
    root->suffix_link = root;
    root->parent = root; // eueueu
    root->up = root;
    for (int i = 0; i < (int)sz; ++i) {
        if (root->next[i] == nullptr) {
            root->next[i] = root;
        }
    }

    queue<Node*> q({root});
    while (q.size()) {
        auto node = q.front();
        q.pop();

        node->suffix_link = node->parent == root ? root : node->parent->suffix_link->next[node->c];
        node->up = node->suffix_link->is_terminal ? node->suffix_link : node->suffix_link->up;
        for (int i = 0; i < (int)sz; ++i) {
            if (node->childs[i] != nullptr) {
                node->next[i] = node->childs[i];
                q.push(node->childs[i]);
            } else {
                node->next[i] = node->parent->suffix_link->next[i];
            }
        }
    }
}

vector<Node*> get_leaves(Node* root) {
    stack<Node*> st;
    st.push(root);

    vector<Node*> ans;
    while (st.size()) {
        auto node = st.top();
        st.pop();

        bool is_leaf = true;
        for (int i = 0; i < (int)sz; ++i) {
            if (node->childs[i] != nullptr) {
                is_leaf = false;
                st.push(node->childs[i]);
            }
        }
        if (is_leaf) {
            ans.push_back(node);
        }
    }

    return ans;
}

vector<int> count_patterns(Node* root, const string& s, const vector<string>& patterns) {
    unordered_map<Node*, int> cnt;

    auto now = root;
    for (int i = 0; i < (int)s.size(); ++i) {
        now = now->next[s[i] - 'a'];
        ++cnt[now->is_terminal ? now : now->up];
    }

    auto leaves = get_leaves(root);
    queue<Node*> q;
    for (auto leaf : leaves) {
        q.push(leaf);
    }

    while (q.size()) {
        auto node = q.front();
        q.pop();

        cnt[node->up] += cnt[node];
        if (q.size() && q.back() != node->parent) {
            q.push(node->parent);
        }
    }

    vector<int> ans;
    for (auto pattern : patterns) {
        auto now = root;
        for (auto c : pattern) {
            now = now->next[c - 'a'];
        }
        ans.push_back(cnt[now]);
    }

    return ans;
}

int main() {
    int n;
    string s;
    cin >> n >> s;

    auto root = make_trie(patterns);
    make_auto(root);

    auto ans = count_patterns(root, s, patterns);
    for (auto i : ans) {
        cout << i << ' ';
    }
    cout << '\n';

    return 0;
}
