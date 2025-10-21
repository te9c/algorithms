#include <bits/stdc++.h>

struct Avlp {
    struct Node {
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;

        unsigned int height = 1;
        unsigned int subTreeCounter = 1;

        int value;
    };

    const int npos = INT_MAX;
    Node* root = nullptr;
    std::function<bool(int,int)> cmp;

    Avlp(std::function<bool(int,int)> _cmp = std::less<int>()) {
        cmp = _cmp;
    }

    // delete if you have a lot of memory
    ~Avlp() {
        std::stack<Node*> s;
        s.push(root);
        while (s.size()) {
            auto nd = s.top();
            s.pop();
            if (nd == nullptr)
                continue;
            if (nd->left != nullptr)
                s.push(nd->left);
            if (nd->right != nullptr)
                s.push(nd->right);
            delete nd;
        }
    }

    void insert (int value) {
        if (root == nullptr) {
            root = new Node();
            root->value = value;
            return;
        }
        insert_internal(root, value);
    }

    int order_of_key(unsigned int k) {
        Node* nd = root;

        if (nd == nullptr || k > nd->subTreeCounter || k == 0) {
            return npos;
        }

        while (k) {
            unsigned int leftCount = 0;
            if (nd->left != nullptr) {
                leftCount = nd->left->subTreeCounter;
            }

            if (k <= leftCount) {
                nd = nd->left;
            }
            else if (k == leftCount + 1) {
                break;
            } else {
                k -= leftCount + 1;
                nd = nd->right;
            }
        }
        return nd->value;
    }

    // ???
    int lower_or_equal_than_x(int x) {
        int ans = 0;
        Node* nd = root;
        while (nd != nullptr) {
            if (cmp(x, nd->value)) {
                nd = nd->left;
            } else {
                int tmp = 1;
                if (nd->left != nullptr) {
                    tmp += nd->left->subTreeCounter;
                }
                ans += tmp;
                nd = nd->right;
            }
        }
        return ans;
    }

    void erase(int value) {
        if (root == nullptr) {
            return;
        }

        erase_internal(root, value);
    }

private:
    void erase_internal(Node *nd, int value) {
        if (nd->value == value) {
            auto lc = nd->left;
            auto rc = nd->right;
            auto par = nd->parent;
            if (lc == nullptr && rc == nullptr) {
                if (par != nullptr) {
                    if (nd == par->left) {
                        par->left = nullptr;
                    } else {
                        par->right = nullptr;
                    }
                } else {
                    root = nullptr;
                }
                delete nd;
                return;
            }
            if (lc == nullptr && rc != nullptr) {
                if (par != nullptr) {
                    if (nd == par->left) {
                        par->left = rc;
                    } else {
                        par->right = rc;
                    }
                } else {
                    root = rc;
                }
                rc->parent = par;
                delete nd;
                return;
            }
            if (lc != nullptr && rc == nullptr) {
                if (par != nullptr) {
                    if (nd == par->left) {
                        par->left = lc;
                    } else {
                        par->right = lc;
                    }
                } else {
                    root = lc;
                }
                lc->parent = par;
                delete nd;
                return;
            }
            auto nd_closest = nd->right;
            while (nd_closest->left != nullptr) {
                nd_closest = nd_closest->left;
            }
            if (nd_closest == nd->right) {
                rc = nd_closest->right;
            } else {
                nd_closest->parent->left = nd_closest->right;
            }

            nd_closest->parent = par;
            nd_closest->left = lc;
            nd_closest->right = rc;
            if (par != nullptr) {
                if (nd == par->left) {
                    par->left = nd_closest;
                } else {
                    par->right = nd_closest;
                }
            } else {
                root = nd_closest;
            }
            lc->parent = nd_closest;
            if (rc != nullptr)
                rc->parent = nd_closest;

            delete nd;
            update_height(nd_closest);
            balance(nd_closest);
            return;
        }

        if (cmp(value, nd->value)) {
            erase_internal(nd->left, value);
        } else {
            erase_internal(nd->right, value);
        }

        update_height(nd);
        balance(nd);
    }

    void insert_internal(Node* nd, int value) {
        // assuming we have set
        if (value == nd->value) {
            return;
        }


        if (cmp(value, nd->value)) {
            if (nd->left == nullptr) {
                nd->left = new Node();
                nd->left->value = value;
                nd->left->parent = nd;
            } else {
                insert_internal(nd->left, value);
            }
        } else {
            if (nd->right == nullptr) {
                nd->right = new Node();
                nd->right->value = value;
                nd->right->parent = nd;
            } else {
                insert_internal(nd->right, value);
            }
        }

        update_height(nd);
        balance(nd);
    }

    int bf(Node* nd) {
        if (nd == nullptr)
            return 0;

        int rp = (nd->right == nullptr ? 0 : nd->right->height);
        int lp = (nd->left == nullptr ? 0 : nd->left->height);
        // return rp - lp;
        return lp - rp;
    }
    void update_height(Node* nd) {
        if (nd == nullptr)
            return;
        nd->height = 1;
        nd->subTreeCounter = 1;
        if (nd->left != nullptr) {
            nd->height = nd->left->height + 1;
            nd->subTreeCounter += nd->left->subTreeCounter;
        }
        if (nd->right != nullptr) {
            nd->height = std::max(nd->height, nd->right->height + 1);
            nd->subTreeCounter += nd->right->subTreeCounter;
        }
    }

    void balance(Node* nd) {
        if (nd == nullptr)
            return;


        if (bf(nd) == -2 && (bf(nd->right) <= 0)) {
            rotate_left(nd);
        }
        else if (bf(nd) == 2 && (bf(nd->left) >= 0)) {
            rotate_right(nd);
        }
        else if (bf(nd) == -2 && bf(nd->right) == 1) {
            big_rotate_left(nd);
        }
        else if (bf(nd) == 2 && bf(nd->left) == -1) {
            big_rotate_right(nd);
        }
    }
    void rotate_left(Node* x) {
        if (x == nullptr)
            return;
        Node* z = x->right;
        if (z == nullptr)
            return;

        Node* t23 = z->left;
        x->right = t23;
        if (t23 != nullptr) {
            t23->parent = x;
        }

        z->left = x;
        if (x->parent != nullptr) {
            if (x->parent->left == x) {
                x->parent->left = z;
            } else {
                x->parent->right = z;
            }
        } else {
            root = z;
        }
        z->parent = x->parent;
        x->parent = z;

        update_height(x);
        update_height(z);
    }
    void rotate_right(Node* x) {
        if (x == nullptr)
            return;
        Node* z = x->left;
        if (z == nullptr)
            return;

        Node* t23 = z->right;
        x->left = t23;
        if (t23 != nullptr) {
            t23->parent = x;
        }

        z->right = x;
        if (x->parent != nullptr) {
            if (x->parent->left == x) {
                x->parent->left = z;
            } else {
                x->parent->right = z;
            }
        } else {
            root = z;
        }
        z->parent = x->parent;
        x->parent = z;
        update_height(x);
        update_height(z);
    }

    void big_rotate_left(Node* x) {
        rotate_right(x->right);
        rotate_left(x);
    }
    void big_rotate_right(Node* x) {
        rotate_left(x->left);
        rotate_right(x);
    }
};

void test_avl() {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::vector<int> vec(20);
    Avlp a;
    for (int i = 0; i < 20; ++i) {
        vec[i] = rng();
        a.insert(vec[i]);
    }
    sort(vec.begin(), vec.end());
    for (int i = 0; i < 20; ++i) {
        if (a.order_of_key(i + 1) != vec[i]) {
            std::cout << "!\n";
            for (int j = 0; j < 20; ++j) {
                std::cout << vec[i] << ' ';
            }
            std::cout << '\n';
            return;
        }
    }
}

int main() {
    // test_avl();
    Avlp avl;

    avl.insert(2);
    avl.insert(3);
    avl.insert(1);
    // avl.erase(2);
    std::cout << avl.lower_or_equal_than_x(1) << '\n';
    // std::cout << avl.order_of_key(2) << '\n';
    // std::cout << avl.order_of_key(1) << '\n';
}
