//次短路
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10005;
const int MAXM = 2000005;
const int inf = 0x3f3f3f3f;
typedef pair<int, int> pii;
int head[MAXN], ecnt;
struct Edge
{
    int to, w, next;
} edges[MAXM];
int dis[MAXN], dis2[MAXN];
bool vis[MAXN];
void init()
{
    ecnt = 0;
    memset(head, -1, sizeof(head));
}
priority_queue<pii, vector<pii>, greater<pii>> que;

void dijkstra(int s)
{
    memset(vis, 0, sizeof vis);
    memset(dis, 0x3f, sizeof dis);
    memset(dis2, 0x3f, sizeof dis2);
    dis[s] = 0;
    que.push(pii(0, s));
    while (!que.empty())
    {
        int u = que.top().second;
        int d = que.top().first;
        que.pop();
        if (dis2[u] < d)
            continue;
        for (int i = head[u]; ~i; i = edges[i].next)
        {
            int d2 = d + edges[i].w;
            if (dis[edges[i].to] > d2)
            {
                swap(dis[edges[i].to], d2);
                que.push(pii(dis[edges[i].to], edges[i].to));
            }
            if (dis2[edges[i].to] > d2 && dis[edges[i].to] <= d2)
            {
                dis2[edges[i].to] = d2;
                que.push(pii(dis2[edges[i].to], edges[i].to));
            }
        }
    }
}
void ade(int u, int v, int w)
{
    edges[ecnt].to = v;
    edges[ecnt].w = w;
    edges[ecnt].next = head[u];
    head[u] = ecnt++;
}
void add(int u, int v, int w)
{
    ade(u, v, w);
    ade(v, u, w);
}
