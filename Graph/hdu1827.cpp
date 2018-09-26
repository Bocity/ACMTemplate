/*
最小点基和最小权点基：
    最小点基=从每个入度为0的SCC中任意选出一个点的集合
    最小权点基=从每个入度为0的SCC中选出最小权值的点的集合
*/
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int INF = 0x7fffffff;
const int MAX = 1005;
int n, m;
int node[MAX];
struct Edge {
    int from;
    int to;
    int next;
};
Edge e[2005];
int head[MAX], edgeNum;

int dfn[MAX], low[MAX], seq;
int stack[MAX], top;
bool inStack[MAX];
int belong[MAX], cnt;
int ind[MAX];
int cost[MAX];

void addEdge(int from, int to) {
    e[edgeNum].from = from;
    e[edgeNum].to = to;
    e[edgeNum].next = head[from];
    head[from] = edgeNum++;
}

int min(int a, int b) {
    return a < b ? a : b;
}

void Tarjan(int u) {
    dfn[u] = low[u] = seq++;
    stack[top++] = u;
    inStack[u] = true;
    for (int i = head[u]; i != -1; i = e[i].next) {
        int w = e[i].to;
        if (dfn[w] < 0) {
            Tarjan(w);
            low[u] = min(low[u], low[w]);
        } else if (inStack[w])
            low[u] = min(low[u], dfn[w]);
    }
    if (dfn[u] == low[u]) {
        int v;
        cnt++;
        do {
            top--;
            v = stack[top];
            inStack[v] = false;
            belong[v] = cnt;
        } while (u != v);
    }
}

void solve() {
    int i;
    for (i = 1; i <= n; i++)
        if (dfn[i] < 0) Tarjan(i);
    for (i = 0; i < edgeNum; i++) {
        if (belong[e[i].from] != belong[e[i].to]) ind[belong[e[i].to]]++;
    }
    for (i = 1; i <= n; i++) {
        if (cost[belong[i]] > node[i]) cost[belong[i]] = node[i];
    }
    int result1 = 0, result2 = 0;
    for (i = 1; i <= cnt; i++) {
        if (ind[i] == 0) {
            result1++;
            result2 += cost[i];
        }
    }
    printf("%d %d\n", result1, result2);
}

int main() {
    int i;
    int from, to;
    while (scanf("%d %d", &n, &m) != EOF) {
        edgeNum = seq = cnt = top = 0;
        memset(head, -1, sizeof(head));
        memset(dfn, -1, sizeof(dfn));
        memset(inStack, 0, sizeof(inStack));
        memset(ind, 0, sizeof(ind));
        for (i = 1; i <= n; i++) cost[i] = INF;
        for (i = 1; i <= n; i++) scanf("%d", &node[i]);
        for (i = 0; i < m; i++) {
            scanf("%d %d", &from, &to);
            addEdge(from, to);
        }
        solve();
    }
    return 0;
}