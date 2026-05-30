#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct Node {
    Node *l = nullptr, *r = nullptr, *par = nullptr;

    int id = -1;
    ll val = 0;
    ll sum = 0;
    bool rev = 0;
    Node(int x, ll y)
        : id(x)
        , val(y)
        , sum(y) { };
    Node() = default;
};

using ptr = Node*;

bool isroot(ptr t) { // true if t root of his SPLAY-tree (not entire tree)
    return t->par == nullptr || (t->par->l != t && t->par->r != t);
}

void push(ptr n) {
    if (!n) {
        return;
    }
    if (n->rev) {
        swap(n->l, n->r);
    }
    if (n->l) {
        n->l->rev ^= n->rev;
    }
    if (n->r) {
        n->r->rev ^= n->rev;
    }
    n->rev = 0;
}

void pull(ptr n) {
    if (!n) {
        return;
    }
    n->sum = n->val;
    if (n->l) {
        push(n->l);
        n->sum += n->l->sum;
    }
    if (n->r) {
        push(n->r);
        n->sum += n->r->sum;
    }
}

void rotate(ptr x) {
    ptr p = x->par, pp = p->par;
    x->par = pp;
    if (pp) {
        if (pp->l == p) {
            pp->l = x;
        } else if (pp->r == p) { // else if bcz of path-pointer
            pp->r = x;
        }
    }
    p->par = x;
    if (p->l == x) {
        // right
        ptr b = x->r;
        p->l = b;
        if (b) {
            b->par = p;
        }
        x->r = p;
    } else {
        ptr b = x->l;
        p->r = b;
        if (b) {
            b->par = p;
        }
        x->l = p;
    }
    pull(p), pull(x);
}

void pushAll(ptr t) { // push on path root->t
    if (!isroot(t)) {
        pushAll(t->par);
    }
    push(t);
}

void splay(ptr x) {
    pushAll(x);
    while (!isroot(x)) {
        ptr p = x->par;
        ptr pp = p->par;
        if (isroot(p)) {
            rotate(x);
        } else if ((p->l == x) == (pp->l == p)) {
            rotate(p), rotate(x);
        } else {
            rotate(x), rotate(x);
        }
    }
}

ptr expose(ptr t) {
    // make root->t preferred path
    // returns last path-pointer or itself (for lca)
    ptr last = nullptr;
    for (ptr i = t; i; last = i, i = i->par) {
        splay(i);
        i->r = last;
        pull(i);
    }
    splay(t);
    return last;
}

void makeroot(ptr t) {
    // make t root of tree (NOT splay-tree)
    expose(t);
    t->rev ^= 1;
    push(t);
}

void link(ptr x, ptr y) {
    makeroot(x);
    x->par = y;
}

void split(ptr x, ptr y) { // make x->y preffered path
    makeroot(x);
    expose(y);
}

void cut(ptr x, ptr y) {
    split(x, y);
    x->par = y->l = nullptr;
    pull(y);
}

void cut(ptr x) { // cut parent-x, x
    expose(x);
    assert(x->l);
    x->l->par = nullptr;
    x->l = nullptr;
    pull(x);
}

bool connected(ptr x, ptr y) {
    makeroot(x);
    expose(y);
    return x == y || x->par != nullptr;
}

int lca(ptr x, ptr y) {
    expose(x);
    return expose(y)->id;
}
