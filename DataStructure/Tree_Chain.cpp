#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 1e5 + 10;
const int N = 1e5 + 10;
int n, m, fa[maxn], dep[maxn], size[maxn];
int root = 1, tot, pos[maxn], son[maxn], tid[maxn], top[maxn];
ll val[maxn];
vector<int> G[maxn];
struct Pair {
    int v1, v2;
    Pair() {}
    Pair(int _v1, int _v2) {
        v1 = _v1, v2 = _v2;
    }
};
Pair operator+(Pair a, Pair b) {
    return Pair((a.v1 + b.v1) % 2019, (a.v2 + b.v2) % 2019);
}
void dfs1(int x, int father, int depth) {
    fa[x] = father, dep[x] = depth;
    size[x] = 1;
    int max_size = 0;
    for (int i = 0; i < G[x].size(); i++) {
        dfs1(G[x][i], x, depth + 1);
        size[x] += size[G[x][i]];
        if (size[G[x][i]] > max_size) {
            max_size = size[G[x][i]];
            son[x] = G[x][i];
        }
    }
}

void dfs2(int x, int root) {
    tid[x] = ++tot, pos[tot] = x, top[x] = root;
    if (son[x]) {
        dfs2(son[x], root);
    }
    for (int i = 0; i < G[x].size(); i++) {
        if (G[x][i] != son[x]) {
            dfs2(G[x][i], G[x][i]);
        }
    }
}

/* 线段树部分
#define LSON l, m, rt << 1
#define RSON m + 1, r, rt << 1 | 1
#define lson rt << 1
#define rson rt << 1 | 1
ll sum2[N << 2], add[N << 2], sum1[N << 2], sum3[N << 2], sum4[N << 2];
// 更新答案
void Maintain(int rt) {
    sum1[rt] = (sum1[lson] + sum1[rson]) % 2019;
    sum2[rt] = (sum2[lson] + sum2[rson]) % 2019;
    return;
}
// 延时标记下传
void Pushdown(int rt) {
    if (add[rt] != 0) { // 倍数变化 add[rt] != 1
        add[rt << 1] += add[rt];
        add[rt << 1 | 1] += add[rt];
        add[rt << 1] %= 2019;
        add[rt << 1 | 1] %= 2019;
        sum1[rt << 1] = (sum1[rt << 1] + add[rt] * sum4[rt << 1]) % 2019;
        sum1[rt << 1 | 1] = (sum1[rt << 1 | 1] + add[rt] * sum4[rt << 1 | 1]) % 2019;
        sum2[rt << 1] = (sum2[rt << 1] + add[rt] * sum3[rt << 1]) % 2019;
        sum2[rt << 1 | 1] = (sum2[rt << 1 | 1] + add[rt] * sum3[rt << 1 | 1]) % 2019;
        add[rt] = 0;
    }
}
void build(int l, int r, int rt = 1) {
    add[rt] = 0; // 倍数变化更改为1
    if (l == r) {
        // cout << val[pos[l]] <<  endl;
        sum1[rt] = val[pos[l]] * size[pos[l]] * size[pos[l]] % 2019;
        sum2[rt] = (val[pos[l]] * size[pos[l]]) % 2019;
        sum3[rt] = size[pos[l]] % 2019;
        sum4[rt] = size[pos[l]] * size[pos[l]] % 2019;
        // cout <<sum3[rt] << endl;
        return;
    }
    int m = (l + r) >> 1;
    build(LSON);
    build(RSON);
    Maintain(rt);
    sum3[rt] = sum3[rt << 1] + sum3[rt << 1 | 1];
    sum4[rt] = sum4[rt << 1] + sum4[rt << 1 | 1];
    sum3[rt] %= 2019;
    sum4[rt] %= 2019;
    return;
}
void update(int L, int R, int c, int l, int r, int rt = 1) {
    if (L > r || R < l) return;
    if (L <= l && r <= R) {
        sum1[rt] = (sum1[rt] + c * sum4[rt]) % 2019;
        sum2[rt] = (sum2[rt] + c * sum3[rt]) % 2019;
        add[rt] += c;
        add[rt] %= 2019;
        return;
    }
    Pushdown(rt);
    int m = (l + r) >> 1;
    if (L <= m) update(L, R, c, LSON);
    if (m < R) update(L, R, c, RSON);
    Maintain(rt);
    return;
}
Pair query(int L, int R, int l, int r, int rt = 1) {
    if (L > r || R < l) return Pair(0, 0);
    if (L <= l && r <= R) {
        return Pair(sum1[rt], sum2[rt]);
    }
    Pushdown(rt);
    int m = (l + r) >> 1;
    return query(L, R, LSON) + query(L, R, RSON);
}
*/
// int lca(int u, int v) {
//     int res;
//     while (top[u] != top[v]) {
//         res = top[v];
//         v = fa[top[v]];
//     }
//     return u == v ? res : son[u];
// }


int lca(int x, int y) {
    int fx = top[x], fy = top[y];
    while (fx != fy) {
        if (dep[fx] > dep[fy])
            x = fa[fx], fx = top[x];
        else
            y = fa[fy], fy = top[y];
    }
    if (dep[x] >= dep[y]) return y;
    return x;
}
void solve_add(int u, int v, ll val) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            swap(u, v);
        }
        update(tid[top[u]], tid[u], val, 1, n);
        u = fa[top[u]];
    }
    if (tid[u] > tid[v]) {
        swap(u, v);
    }
    update(tid[u], tid[v], val, 1, n);
}
Pair solve_query(int u, int v) {
    Pair sum = Pair(0,0);
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            swap(u, v);
        }
        sum = sum + query(tid[top[u]], tid[u], 1, n);
        u = fa[top[u]];
    }
    if (tid[u] > tid[v]) {
        swap(u, v);
    }
    sum = sum +  query(tid[u], tid[v], 1, n);
    return sum;
}

void update_subtree(int v, ll val) {
    if (v == root) {
        update(1, n, val, 1, n);
        return;
    }
    if (tid[v] > tid[root] || tid[v] + size[v] - 1 < tid[root] + size[root] - 1) {
        update(tid[v], tid[v] + size[v] - 1, val, 1, n);
        return;
    }
    int u = lca(v, root);
    update(1, tid[u] - 1, val, 1, n), update(tid[u] + size[u], n, val, 1, n);
}

Pair query_subtree(int v) {
    if (v == root) {
        return query(1, n, 1, n);
    }
    if (tid[v] > tid[root] || tid[v] + size[v] - 1 < tid[root] + size[root] - 1) {
        return query(tid[v], tid[v] + size[v] - 1, 1, n);
    }
    int u = lca(v, root);
    return query(1, tid[u] - 1, 1, n) + query(tid[u] + size[u], n, 1, n);
}



int main() {
    int M;
    scanf("%d%d", &n, &M);
    root = 1;
    for (int i = 2; i <= n; i++) {  // m为i的父亲 
        scanf("%d%lld", &m, &val[i]);
        G[m].push_back(i);    
    }
    tot = 0;
    dfs1(root, 0, 0), dfs2(root, 0);
    build(1, n);
    char op[20];
    while (M--) {
        int x, y, z;
        scanf("%s", op);
        if (op[0] == 'I') {
            scanf("%d%d%d", &x, &y, &z);
            solve_add(x, y, z);   
            int rt = lca(x, y);
            solve_add(rt, rt, -z);//压点为边的操作
            // cout << rt << endl;
        } else {
            scanf("%d", &x);
            ll ans = 0;
            Pair tmp = query_subtree(x);
            // cout << tmp.v1 << " " << tmp.v2 << endl;
            ans = tmp.v2 * (size[x]) - tmp.v1;
            printf("%lld\n", (ans + 2019) % 2019);
        }
    }
    return 0;
}