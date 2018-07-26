#include <algorithm>
#include <cstdio>
#define nullptr NULL
const int maxN = 1e5 + 3;
typedef int intvec[maxN];
// splay tree
struct Node;
Node *root;
void print_tree(Node *);
void print_list(Node *);
int N;
// void print_tree(Node*);
struct Node {
    int data, adding, min_data, degree;
    bool rev;
    Node *parent, *left, *right;
    Node(int d)
        : data(d)
        , adding(0)
        , min_data(d)
        , degree(1)
        , rev(false)
        , parent(nullptr)
        , left(nullptr)
        , right(nullptr) {}
    void push_down() {
        if (adding) {
            if (left) {
                left->data += adding;
                left->min_data += adding;
                left->adding += adding;
            }
            if (right) {
                right->data += adding;
                right->min_data += adding;
                right->adding += adding;
            }
            adding = 0;
        }
        if (rev) {
            if (left) {
                std::swap(left->left, left->right);
                left->rev ^= 1;
            }
            if (right) {
                std::swap(right->left, right->right);
                right->rev ^= 1;
            }
            rev = false;
        }
    }
    void update() {
        min_data = data;
        if (left && left->min_data < min_data) min_data = left->min_data;
        if (right && right->min_data < min_data) min_data = right->min_data;
        degree = 1;
        if (left) degree += left->degree;
        if (right) degree += right->degree;
    }
    Node *LeftMost() {
        Node *nd = this;
        while (true) {
            nd->push_down();
            if (nd->left)
                nd = nd->left;
            else
                break;
        }
        return nd;
    }
    Node *RightMost() {
        Node *nd = this;
        while (true) {
            nd->push_down();
            if (nd->right)
                nd = nd->right;
            else
                break;
        }
        return nd;
    }
    Node *prev() {
        splay();
        if (left)
            return left->RightMost();
        else
            return nullptr;
    }
    Node *next() {
        splay();
        if (right)
            return right->LeftMost();
        else
            return nullptr;
    }
    void RotateRight() {
        Node *grandparent = parent->parent;
        if (parent == root)
            root = this;
        else if (parent == parent->parent->left)
            parent->parent->left = this;
        else
            parent->parent->right = this;
        parent->parent = this;
        parent->left = right;
        if (right) right->parent = parent;
        right = parent;
        parent = grandparent;
        right->update();
        update();
    }
    void RotateLeft() {
        Node *grandparent = parent->parent;
        if (parent == root)
            root = this;
        else if (parent == parent->parent->left)
            parent->parent->left = this;
        else
            parent->parent->right = this;
        parent->parent = this;
        parent->right = left;
        if (left) left->parent = parent;
        left = parent;
        parent = grandparent;
        left->update();
        update();
    }
    void splay(Node *target = nullptr) {
        while (parent != target) {
            if (parent->parent == target) {
                parent->push_down();
                push_down();
                if (this == parent->left)
                    RotateRight();
                else
                    RotateLeft();
            } else {
                parent->parent->push_down();
                parent->push_down();
                push_down();
                if (this == parent->left) {
                    if (parent == parent->parent->left)
                        parent->RotateRight(), RotateRight();
                    else
                        RotateRight(), RotateLeft();
                } else {
                    if (parent == parent->parent->right)
                        parent->RotateLeft(), RotateLeft();
                    else
                        RotateLeft(), RotateRight();
                }
            }
        }
        push_down();
        if (!target) root = this;
    }
    Node *kth(int k) {
        if (k == 0 || k > degree) return nullptr;
        Node *now = this;
        while (true) {
            now->push_down();
            if ((now->left && k == now->left->degree + 1) || (!now->left && k == 1)) {
                return now;
            } else if (now->left && k < now->left->degree + 1)
                now = now->left;
            else {
                if (now->left) k -= now->left->degree;
                --k;
                now = now->right;
            }
        }
        return nullptr;
    }
    int nth() {
        splay();
        int rt = 1;
        if (left) rt += left->degree;
        return rt;
    }
    Node *drop() {
        --N;
        Node *Prev = prev(), *Next = next();
        if (Prev) {
            Prev->splay();
            if (Next) {
                Next->splay(Prev);
                Next->left = nullptr;
                Next->update();
                Prev->update();
            } else {
                Prev->right = nullptr;
                Prev->update();
            }
        } else {
            if (Next) {
                Next->splay();
                Next->left = nullptr;
                Next->update();
            } else
                root = nullptr;
        }
        left = right = parent = nullptr;
        return this;
    }
    Node *insert_back(Node *it) {
        ++N;
        if (!it) {
            if (!root) {
                root = this;
                return this;
            }
            Node *lefm = root->LeftMost();
            lefm->splay();
            parent = lefm;
            lefm->left = this;
            lefm->update();
            return this;
        }
        Node *next = it->next();
        it->splay();
        if (next) {
            next->splay(it);
            next->left = this;
            parent = next;
            next->update();
            it->update();
        } else {
            it->right = this;
            parent = it;
            it->update();
        }
        return this;
    }
};

void destroy(Node *n) {
    if (!n) return;
    destroy(n->left);
    destroy(n->right);
    delete n;
}

Node *part(int A, int B) {
    Node *next = root->kth(B + 1), *prev = root->kth(A - 1);
    if (prev) {
        prev->splay();
        if (next) {
            next->splay(prev);
            return next->left;
        } else
            return prev->right;
    } else {
        if (next) {
            next->splay();
            return next->left;
        } else
            return root;
    }
}
void add(int A, int B, int D) {
    Node *r = part(A, B);
    r->data += D;
    r->min_data += D;
    r->adding += D;
    while (r->parent) {
        r->parent->update();
        r = r->parent;
    }
}
void insert(int A, int x) {
    Node *n = new Node(x);
    Node *it = root ? root->kth(A) : nullptr;
    n->insert_back(it);
}
void drop(int A) {
    Node *it = root->kth(A);
    delete it->drop();
}
void reverse(int A, int B) {
    Node *r = part(A, B);
    std::swap(r->left, r->right);
    r->rev ^= 1;
}
void revolve(int A, int B, int T) {
    int len = B - A + 1;
    T = (T % len + len) % len;
    if (!T) return;
    Node *r = part(A, B), *p = r->parent;
    Node *rt = r->kth(len - T);
    rt->splay(p);
    Node *top = rt->right;
    rt->right = nullptr;
    top->parent = nullptr;
    rt->update();
    Node *lefm = rt->LeftMost();
    lefm->splay(p);
    lefm->left = top;
    top->parent = lefm;
    lefm->update();
}
int min(int A, int B) {
    Node *r = part(A, B);
    r->push_down();
    return r->min_data;
}

void print_tree(Node *n) {
    if (!n) {
        std::printf("EMPTY!\n");
        return;
    }
    std::printf("root %d(+%d)[%d] with degree %d and rev %d:\n", n->data, n->adding, n->min_data, n->degree, n->rev);
    std::printf("LEFT : \n");
    print_tree(n->left);
    std::printf("RIGHT : \n");
    print_tree(n->right);
    std::printf("root %d - fin -\n", n->data);
}
intvec ans;
int ans_cnt;
void print_list(Node *n) {
    n->push_down();
    if (n->left) print_list(n->left);
    ans[ans_cnt++] = n->data;
    if (n->right) print_list(n->right);
}

int nums[maxN];
void build(int a, int b, Node *r, bool ch) {
    if (a > b) return;
    if (a == b) {
        Node *n = new Node(nums[a]);
        n->parent = r;
        if (!ch) {
            if (r)
                r->left = n;
            else
                root = n;
        } else {
            if (r)
                r->right = n;
            else
                root = n;
        }
        return;
    }
    int mid = (a + b) >> 1;
    Node *n = new Node(nums[mid]);
    n->parent = r;
    if (!ch) {
        if (r)
            r->left = n;
        else
            root = n;
    } else {
        if (r)
            r->right = n;
        else
            root = n;
    }
    build(a, mid - 1, n, false);
    build(mid + 1, b, n, true);
}
void dfs(Node *r) // call only once
{
    if (!r) return;
    dfs(r->left);
    dfs(r->right);
    r->update();
}

int main() {
    int M, a, b;
    std::scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; ++i) nums[i] = i;
    build(1, N, nullptr, false);
    dfs(root);
    while (M--) {
        std::scanf("%d %d", &a, &b);
        revolve(1, a + b - 1, b);
    }
    ans_cnt = 0;
    print_list(root);
    for (int i = 0; i < N; ++i) {
        std::printf("%d", ans[i]);
        if (i == N - 1)
            std::printf("\n");
        else
            std::printf(" ");
    }
}
