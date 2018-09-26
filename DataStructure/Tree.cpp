/*
本题一共有22个操作：
第一行是N和M，表示有这棵树有N个点M个询问
然后是N-1行，每行x,y表示x-y有一条边
接下去是N行，每行是一个数字，表示每个点的权值
后面一行表示根
接下来是M行
第一个数字是K
K=0 表示换根，后面x，表示把这棵树的根变成x
K=1 表示点修改，后面x,y 表示把点x的权值改为y
K=2 表示点增加，后面x,y 表示把点x的权值增加y
K=3 表示点翻倍，后面x,y 表示把点x的权值翻y倍
K=4 表示点询问权值，后面x 表示询问这个点的权值
K=5 表示链修改，后面x,y,z，表示把这棵树中x-y的路径上点权值改成z
K=6 表示链增加，后面x,y,z，表示把这棵树中x-y的路径上点权值增加z
K=7 表示链翻倍，后面x,y,z，表示把这棵树中x-y的路径上点权值翻z倍
K=8 表示链询问min，后面x,y，表示询问这棵树中x-y的路径上点的min
K=9 表示链询问max，后面x,y，表示询问这棵树中x-y的路径上点的max
K=10 表示链询问sum，后面x,y，表示询问这棵树中x-y的路径上点的sum
K=11 表示链询问siz，后面x,y，表示询问这棵树中x-y的路径上点的多少
K=12 表示子树修改，后面x,y，表示以x为根的子树的点权值改成y
K=13 表示子树增加，后面x,y，表示以x为根的子树的点权值增加y
K=14 表示子树翻倍，后面x,y，表示以x为根的子树的点权值翻y倍
K=15 表示子树询问min，后面x，表示询问以x为根的子树的点的min
K=16 表示子树询问max，后面x，表示询问以x为根的子树的点的max
K=17 表示子树询问sum，后面x，表示询问以x为根的子树的点的sum
K=18 表示子树询问siz，后面x，表示询问以x为根的子树的点的多少
K=19 表示换父亲，后面x,y，表示把x的父亲换成y，如果y在x子树里不操作
K=20 表示询问子树，后面x,y, 表示询问y是否在x的子树内，输出true/false
K=21 表示查询父亲，后面x，表示询问x的父亲的点权值，若没有父亲则输出-1
input
5 30
1 2
2 3
3 4
4 5
1 -2 3 -1 2
3
0 2
1 2 2
2 3 1
3 5 5
4 2
5 3 2 5
6 1 4 3
7 4 5 2
8 5 3
9 2 5
10 1 5
11 3 4
12 4 -3
13 2 -1
14 3 4
15 2
16 2
17 4
18 4
19 4 1
20 1 4
21 1
14 1 4
15 3
18 1
19 5 3
21 5
13 3 1
4 5
17 2

output
2
4
20
44
2
-16
28
-32
2
true
7
28
3
28
-63
-79
*/
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#define PAU putchar(' ')
#define ENT putchar('\n')
#define CH                                                                                                             \
    for (int d = 0; d <= 1; d++)                                                                                       \
        if (ch[d])
using namespace std;
const int maxn = 100000 + 10, inf = 1 << 29;
struct info {
    long long mi, mx, siz, sm;
} null = (info){inf, -inf, 0, 0};
struct tag {
    int mul, add;
    bool empty() {
        return (mul == 1 && add == 0);
    }
} nulltag = (tag){1, 0};
info operator+(const info &a, const info &b) {
    return (info){min(a.mi, b.mi), max(a.mx, b.mx), a.siz + b.siz, a.sm + b.sm};
}
info operator+(const info &a, const tag &b) {
    return a.siz ? (info){a.mi * b.mul + b.add, a.mx * b.mul + b.add, a.siz, a.sm * b.mul + b.add * a.siz} : null;
}
tag operator+(const tag &a, const tag &b) {
    return (tag){a.mul * b.mul, a.add * b.mul + b.add};
}
struct snode {
    snode *ch[2], *fa;
    info x, sm;
    tag od, all;
    void init() {
        x = sm = null;
        od = all = nulltag;
        ch[0] = ch[1] = fa = NULL;
        return;
    }
    snode() {
        x = sm = null;
        od = all = nulltag;
        ch[0] = ch[1] = fa = NULL;
    }
    void addt(tag a) {
        od = od + a;
        all = all + a;
        x = x + a;
        sm = sm + a;
        return;
    }
    void down() {
        if (!od.empty()) {
            CH {
                ch[d]->addt(od);
            };
            od = nulltag;
        }
        return;
    }
    void update() {
        sm = x;
        CH {
            sm = sm + ch[d]->sm;
        }
        return;
    }
} Splay[maxn], *root[maxn];
int parent(snode *x, snode *&y) {
    return (y = x->fa) ? y->ch[1] == x ? 1 : y->ch[0] == x ? 0 : -1 : -1;
}
static void rotate(snode *x) {
    snode *y, *z;
    int d1 = parent(x, y), d2 = parent(y, z);
    if (y->ch[d1] = x->ch[d1 ^ 1]) y->ch[d1]->fa = y;
    y->fa = x;
    x->fa = z;
    x->ch[d1 ^ 1] = y;
    if (d2 != -1) z->ch[d2] = x;
    y->update();
    return;
}
void pushdown(snode *x) {
    static snode *s[maxn];
    int top = 0;
    for (snode *y;; x = y) {
        s[top++] = x;
        y = x->fa;
        if (!y || (y->ch[0] != x && y->ch[1] != x)) break;
    }
    while (top--) s[top]->down();
    return;
}
static snode *splay(snode *x) {
    pushdown(x);
    snode *y, *z;
    int d1, d2;
    while (true) {
        if ((d1 = parent(x, y)) < 0) break;
        if ((d2 = parent(y, z)) < 0) {
            rotate(x);
            break;
        }
        if (d1 == d2)
            rotate(y), rotate(x);
        else
            rotate(x), rotate(x);
    }
    x->update();
    return x;
}
snode *join(snode *x, snode *y) {
    if (!x) return y;
    if (!y) return x;
    while (x->ch[1]) x->down(), x = x->ch[1];
    splay(x)->ch[1] = y;
    y->fa = x;
    x->update();
    return x;
}
struct node {
    node *ch[2], *fa, *s[2];
    info x, sm, sb, all;
    tag cha, tre;
    bool rev;
    int id;
    void revt() {
        swap(ch[0], ch[1]);
        swap(s[0], s[1]);
        rev ^= 1;
        return;
    }
    void chat(tag a) {
        x = x + a;
        sm = sm + a;
        cha = cha + a;
        all = sm + sb;
        return;
    }
    void tret(tag a) {
        tre = tre + a;
        sb = sb + a;
        all = sm + sb;
        if (root[id]) root[id]->addt(a);
        return;
    }
    void down() {
        if (rev) {
            CH {
                ch[d]->revt();
            }
            rev = false;
        }
        if (!cha.empty()) {
            CH {
                ch[d]->chat(cha);
            }
            cha = nulltag;
        }
        if (!tre.empty()) {
            CH {
                ch[d]->tret(tre);
            }
            tre = nulltag;
        }
        return;
    }
    void update() {
        sm = x;
        sb = null;
        if (root[id]) sb = sb + root[id]->sm;
        CH {
            sm = sm + ch[d]->sm;
            sb = sb + ch[d]->sb;
        }
        all = sm + sb;
        s[0] = ch[0] ? ch[0]->s[0] : this;
        s[1] = ch[1] ? ch[1]->s[1] : this;
        return;
    }
} lct[maxn];
int parent(node *x, node *&y) {
    return (y = x->fa) ? y->ch[1] == x ? 1 : y->ch[0] == x ? 0 : -1 : -1;
}
void rotate(node *x) {
    node *y, *z;
    int d1 = parent(x, y), d2 = parent(y, z);
    if (y->ch[d1] = x->ch[d1 ^ 1]) y->ch[d1]->fa = y;
    y->fa = x;
    x->fa = z;
    x->ch[d1 ^ 1] = y;
    if (d2 != -1) z->ch[d2] = x;
    y->update();
    return;
}
void pushdown(node *x) {
    static node *s[maxn];
    int top = 0;
    for (node *y;; x = y) {
        s[top++] = x;
        y = x->fa;
        if (!y || (y->ch[0] != x && y->ch[1] != x)) break;
    }
    while (top--) s[top]->down();
    return;
}
node *splay(node *x) {
    pushdown(x);
    node *y, *z;
    int d1, d2;
    while (true) {
        if ((d1 = parent(x, y)) < 0) break;
        if ((d2 = parent(y, z)) < 0) {
            rotate(x);
            break;
        }
        if (d1 == d2)
            rotate(y), rotate(x);
        else
            rotate(x), rotate(x);
    }
    x->update();
    return x;
}
void add(snode *x, snode *&y, info tag) {
    x->init();
    x->x = tag;
    x->ch[0] = y;
    if (y) y->fa = x;
    x->update();
    y = x;
    return;
}
void detach(node *x) {
    add(x->ch[1]->s[0]->id + Splay, root[x->id], x->ch[1]->all);
    return;
}
void connect(node *x, node *y) {
    snode *p = y->s[0]->id + Splay;
    splay(p);
    if (p->ch[0]) p->ch[0]->fa = NULL;
    if (p->ch[1]) p->ch[1]->fa = NULL;
    root[x->id] = join(p->ch[0], p->ch[1]);
    y->chat(p->all);
    y->tret(p->all);
    return;
}
node *access(node *x) {
    node *ret = NULL;
    for (; x; x = x->fa) {
        if (splay(x)->ch[1]) detach(x);
        if (x->ch[1] = ret) connect(x, ret);
        (ret = x)->update();
    }
    return ret;
}
void makeroot(int x) {
    access(x + lct)->revt();
    return;
}
void link(int x, int y) {
    access(lct + y);
    splay(lct + y)->ch[1] = lct + x;
    makeroot(x);
    splay(lct + x)->fa = lct + y;
    return;
}
node *findfa(node *x) {
    x = splay(x)->ch[0];
    if (!x)
        return x;
    else
        return x->s[1];
}
int queryfa(int x) {
    node *t;
    access(x + lct);
    if (!(t = findfa(x + lct)))
        return -1;
    else
        return t->x.sm;
}
int treeroot;
node *findtop(node *x) {
    return splay(x)->s[0];
}
bool insub(int x, int y) {
    if (x == y || x == treeroot) return true;
    access(y + lct);
    if (findtop(x + lct) == findtop(y + lct)) return true;
    return false;
}
void changesub(int x, int y, tag t) {
    makeroot(x);
    access(lct + y);
    splay(lct + y);
    lct[y].x = lct[y].x + t;
    if (root[y]) root[y]->addt(t);
    lct[y].update();
    return;
}
void changecha(int x, int y, tag t) {
    makeroot(x);
    access(lct + y)->chat(t);
    return;
}
info querycha(int x, int y) {
    makeroot(x);
    return access(lct + y)->sm;
}
info querysub(int x, int y) {
    makeroot(x);
    access(lct + y);
    splay(lct + y);
    return root[y] ? lct[y].x + root[y]->sm : lct[y].x;
}
void cutfa(int x) {
    node *t = (access(lct + x), splay(lct + x));
    t->ch[0] = t->ch[0]->fa = NULL;
    t->update();
    return;
}
void linkfa(int x, int fa) {
    access(fa + lct);
    splay(lct + fa);
    makeroot(x);
    splay(lct + x)->fa = lct + fa;
    lct[fa].update();
    add(Splay + x, root[fa], lct[x].all);
    return;
}
void splitfa(int r, int x, int fa) {
    makeroot(r);
    if ((access(lct + x), access(lct + fa)) == lct + x) return;
    cutfa(x);
    linkfa(x, fa);
    return;
}
int n, Q, p1[maxn], p2[maxn], A[maxn];
void inittree(int *a) {
    for (int i = 1; i <= n; i++) {
        lct[i].id = i;
        lct[i].s[0] = lct[i].s[1] = lct + i;
        lct[i].x = lct[i].sm = lct[i].all = (info){a[i], a[i], 1, a[i]};
        lct[i].cha = lct[i].tre = nulltag;
    }
    return;
}
inline int read() {
    int x = 0, sig = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') sig = -1;
        ch = getchar();
    }
    while (isdigit(ch)) x = 10 * x + ch - '0', ch = getchar();
    return x *= sig;
}
inline void write(long long x) {
    if (x == 0) {
        putchar('0');
        return;
    }
    if (x < 0) putchar('-'), x = -x;
    int len = 0;
    static long long buf[20];
    while (x) buf[len++] = x % 10, x /= 10;
    for (int i = len - 1; i >= 0; i--) putchar(buf[i] + '0');
    return;
}
void init() {
    n = read();
    Q = read();
    for (int i = 2; i <= n; i++) p1[i] = read(), p2[i] = read();
    for (int i = 1; i <= n; i++) A[i] = read();
    inittree(A);
    for (int i = 2; i <= n; i++) link(p1[i], p2[i]);
    treeroot = read();
    makeroot(treeroot);
    return;
}
void work() {
    int x, y, z, tp;
    while (Q--) {
        tp = read();
        x = read();
        switch (tp) {
            case 0:
                makeroot(x), treeroot = x;
                break;
            case 1:
                changecha(x, x, (tag){0, read()});
                break;
            case 2:
                changecha(x, x, (tag){1, read()});
                break;
            case 3:
                changecha(x, x, (tag){read(), 0});
                break;
            case 4:
                write(querycha(x, x).mi);
                ENT;
                break;
            case 5:
                y = read();
                changecha(x, y, (tag){0, read()});
                break;
            case 6:
                y = read();
                changecha(x, y, (tag){1, read()});
                break;
            case 7:
                y = read();
                changecha(x, y, (tag){read(), 0});
                break;
            case 8:
                y = read();
                write(querycha(x, y).mi);
                ENT;
                break;
            case 9:
                y = read();
                write(querycha(x, y).mx);
                ENT;
                break;
            case 10:
                y = read();
                write(querycha(x, y).sm);
                ENT;
                break;
            case 11:
                y = read();
                write(querycha(x, y).siz);
                ENT;
                break;
            case 12:
                changesub(treeroot, x, (tag){0, read()});
                break;
            case 13:
                changesub(treeroot, x, (tag){1, read()});
                break;
            case 14:
                changesub(treeroot, x, (tag){read(), 0});
                break;
            case 15:
                write(querysub(treeroot, x).mi);
                ENT;
                break;
            case 16:
                write(querysub(treeroot, x).mx);
                ENT;
                break;
            case 17:
                write(querysub(treeroot, x).sm);
                ENT;
                break;
            case 18:
                write(querysub(treeroot, x).siz);
                ENT;
                break;
            case 19:
                y = read();
                splitfa(treeroot, x, y);
                break;
            case 20:
                y = read();
                if (insub(x, y))
                    puts("true");
                else
                    puts("false");
                break;
            case 21:
                write(queryfa(x));
                ENT;
                break;
        }
    }
    return;
}
void print() {
    return;
}
int main() {
    init();
    work();
    print();
    return 0;
}