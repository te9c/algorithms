struct SuffixTree {
    const ll inf = INT_MAX;

    vector<map<char,int>> next;
    vector<ll> len, first_pos;
    vector<int> suffix_link;
    int sz = 1;
    string s;

    ll node = 0, pos = 0; // max_non_unique suffix
                           // is like length of the suffix
    SuffixTree() {
        next.emplace_back();
        len.emplace_back(inf);
        first_pos.emplace_back(0);
        suffix_link.emplace_back(0);
    }

    int make_node(ll _pos, ll _len) {
        next.emplace_back();
        first_pos.emplace_back(_pos);
        len.emplace_back(_len);
        suffix_link.emplace_back(0);
        return sz++;
    }

    int getnext(int i, int j) {
        if (next[i].count(j))
            return next[i][j];
        return 0;
    }

    void go_edge() {
        while (pos > len[getnext(node, s[(int)s.size() - pos])]) {
            node = next[node][s[(int)s.size() - pos]];
            pos -= len[node];
        }
    }

    void add_char(char c) {
        s.push_back(c);
        ++pos;
        int last = 0;

        while (pos > 0) {
            go_edge();
            int edge = s[(int)s.size() - pos];
            int& v = next[node][edge];
            int t = s[first_pos[v] + pos - 1];
            if (v == 0) {
                // rule 1
                v = make_node((int)s.size() - pos, inf);
                suffix_link[last] = node;
                last = 0; // ?
            } else if (t == c) {
                // rule 3
                suffix_link[last] = node;
                return;
            } else {
                // rule 2
                int u = make_node(first_pos[v], pos - 1);
                next[u][c] = make_node((int)s.size() - 1, inf);
                next[u][t] = v;
                first_pos[v] += pos - 1;
                if (len[v] != inf)
                    if (len[v] != inf)
                v = u;
                suffix_link[last] = u;
                last = u;
            }

            if (node == 0)
                --pos;
            else
                node = suffix_link[node];
        }
    }
};
