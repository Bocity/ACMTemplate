#include <bits/stdc++.h>
#define REP(i, x, n) for (int i = (x); i < (n); ++i)
#define PER(i, x, n) for (int i = (n) -1; i >= x; --i)
#define endl "\n"
#define DE puts("----------")
#define CASE(i, ans) cout << "Case #" << (i) << ": " << (ans) << "\n"
#define lowbit(x) ((x) & (-(x)))
#define sqr(x) ((x) * (x))
#define eps 1e-9
#define PI acos(-1.0)
#define MOD 1000000007
using namespace std;
typedef long long ll;
const int inf = 1 << 29, N = 1000, M = 100010;
int head[N], ver[N], edge[M], Next[M], d[N];
int n, m, s, t, tot, maxflow;
queue<int> q;
void add(int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z, Next[tot] = head[x], head[x] = tot;
    ver[++tot] = x, edge[tot] = 0, Next[tot] = head[y], head[y] = tot;
}
bool bfs() {
    memset(d, 0, sizeof d);
    while (q.size()) q.pop();
    q.push(s);
    d[s] = 1;
    while (q.size()) {
        int x = q.front();
        q.pop();
        for (int i = head[x]; i; i = Next[i]) {
            if (edge[i] && !d[ver[i]]) {
                q.push(ver[i]);
                d[ver[i]] = d[x] + 1;
                if (ver[i] == t) return 1;
            }
        }
    }
    return 0;
}
int dinic(int x, int flow) {
    if (x == t) return flow;
    int rest = flow, k;
    for (int i = head[x]; i && rest; i = Next[i]) {
        if (edge[i] && d[ver[i]] == d[x] + 1) {
            k = dinic(ver[i], min(rest, edge[i]));
            if (!k) d[ver[i]] = 0;
            edge[i] -= k;
            edge[i ^ 1] += k;
            rest -= k;
        }
    }
    return flow - rest;
}
int a, b;
int main() {
    scanf("%d%d", &n, &m);
    REP(i, 1, m + 1) {
        add(n + 1, i, 1);
    }
    REP(i, m + 1, n + 1) {
        add(i, n + 2, 1);
    }
    while (~scanf("%d%d", &a, &b)) {
        add(a, b, inf);
    }
    s = n + 1;
    t = n + 2;
    int flow;
    while (bfs()) {
        while (flow = dinic(s, inf)) maxflow += flow;
    }
    printf("%d\n", maxflow);
    return 0;
}
