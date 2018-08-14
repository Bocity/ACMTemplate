#include <bits/stdc++.h>
#define MAXN 300006
using namespace std;
struct Node {
    int val, size;
    Node *ls, *rs;
    void pushup() {
        if (ls == NULL) return;
        size = ls->size + rs->size;
        val = rs->val;
    } //与线段树同样具有pushup
    Node(int v, int s, Node *l, Node *r)
        : val(v)
        , size(s)
        , ls(l)
        , rs(r) {}
    Node() {}
} pool[MAXN];
int cnt = 0;
Node *root = NULL;
Node *NewNode(int val, int size, Node *ls, Node *rs) {
    pool[cnt] = Node(val, size, ls, rs);
    return &pool[cnt++]; //节点池建新点，new,delete太慢
}
int find(int k, Node *rt) {
    if (rt->size == 1) return rt->val;
    if (k <= rt->ls->size)
        return find(k, rt->ls);
    else
        return find(k - rt->ls->size, rt->rs); //找排名为k的点。
}
int Rank(int x, Node *rt) //找一个点的排名，因为根节点存的是两个子树中大的一个，也就是右子树的值，所以要与左子树比较
{
    if (rt->size == 1) {
        return 1;
    } else {
        if (x <= rt->ls->val) {
            return Rank(x, rt->ls);
        } else {
            return Rank(x, rt->rs) + rt->ls->size;
        }
    }
}
inline void maintain(Node *rt) //旋转，平衡系数设为4倍时旋转
{
    if (rt->ls->size > rt->rs->size * 4) {
        rt->rs = NewNode(rt->rs->val, rt->ls->rs->size + rt->rs->size, rt->ls->rs, rt->rs);
        Node *tmp = rt->ls;
        rt->ls = rt->ls->ls;
        *tmp = *rt->rs;
        rt->rs = tmp; //垃圾回收，下面同理
        cnt--;
    } else if (rt->ls->size * 4 < rt->rs->size) {
        rt->ls = NewNode(rt->rs->ls->val, rt->rs->ls->size + rt->ls->size, rt->ls, rt->rs->ls);
        Node *tmp = rt->rs;
        rt->rs = rt->rs->rs;
        *tmp = *rt->ls;
        rt->ls = tmp;
        cnt--;
    }
}
void ins(int val, Node *&rt) //插入，同时向上pushup使得其满足类似线段树的那个性质
{
    if (rt == NULL) {
        rt = NewNode(val, 1, NULL, NULL);
        return;
    }
    if (rt->size == 1) {
        rt->ls = NewNode(min(val, rt->val), 1, NULL, NULL);
        rt->rs = NewNode(max(val, rt->val), 1, NULL, NULL);
    } else {
        if (val > rt->ls->val)
            ins(val, rt->rs);
        else
            ins(val, rt->ls);
    }
    rt->pushup();
    maintain(rt);
}
void del(Node *rt, Node *fa, int val) //删除，直接跑到最后一层，将另一个子树提上来做父亲，同时向上pushup,这就是为啥很多人叫它宗法树,兄弟做父亲2333，类似继位
{
    if (rt->size == 1)
        *fa = fa->ls->val == val ? *fa->rs : *fa->ls;
    else {
        if (val <= rt->ls->val)
            del(rt->ls, rt, val);
        else
            del(rt->rs, rt, val);
    }
    rt->pushup();
}
int main() {
    int n;
    scanf("%d", &n);
    root = NewNode(2147483647, 1, NULL, NULL);
    for (int i = 1; i <= n; i++) {
        int opt, x;
        scanf("%d %d", &opt, &x);
        if (opt == 1) ins(x, root);
        if (opt == 2) del(root, NULL, x);
        if (opt == 3) printf("%d\n", Rank(x, root));
        if (opt == 4) printf("%d\n", find(x, root));
        if (opt == 5) printf("%d\n", find(Rank(x, root) - 1, root));
        if (opt == 6) printf("%d\n", find(Rank(x + 1, root), root));
    }
}