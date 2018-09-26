// 有带权图G, 对于图中每条边e[i], 都有benifit[i](收入)和cost[i](花费), 我们要求的是一棵生成树T, 它使得 ∑(benifit[i]) / ∑(cost[i]), i∈T 最大(或最小).
// 这显然是一个具有现实意义的问题.
// 设x[i]等于1或0, 表示边e[i]是否属于生成树.
// 则我们所求的比率 r = ∑(benifit[i] * x[i]) / ∑(cost[i] * x[i]), 0≤i<m .
// 为了使 r 最大, 设计一个子问题---> 让 z = ∑(benifit[i] * x[i]) - l * ∑(cost[i] * x[i]) = ∑(d[i] * x[i]) 最大 (d[i] = benifit[i] - l * cost[i]) , 并记为z(l). 我们可以兴高采烈地把z(l)看做以d为边权的最大生成树的总权值.
// 然后明确两个性质:
// 　1.  z单调递减
// 　　证明: 因为cost为正数, 所以z随l的减小而增大.
// 　2.  z( max(r) ) = 0
// 　　证明: 若z( max(r) ) < 0, ∑(benifit[i] * x[i]) - max(r) * ∑(cost[i] * x[i]) < 0, 可化为 max(r) < max(r). 矛盾;
// 　　        若z( max(r) ) >= 0, 根据性质1, 当z = 0 时r最大. 
// 到了这个地步, 七窍全已打通, 喜欢二分的上二分, 喜欢Dinkelbach的就Dinkelbach.


/*
ID: wuqi9395@126.com
PROG:
LANG: C++
*/
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#define maxn 1010
#define INF (1 << 30)
#define PI acos(-1.0)
#define mem(a, b) memset(a, b, sizeof(a))
#define For(i, n) for (int i = 0; i < n; i++)
#define eps (1e-5)
          typedef long long ll;

//二分法 复杂度较高
using namespace std;
int n, vis[maxn], pre[maxn];
struct node {
    int x, y, z;
} p[maxn];
double edge[maxn][maxn];
void init() {
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &p[i].x, &p[i].y, &p[i].z);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++)
            edge[i][j] = edge[j][i] = sqrt((p[i].x - p[j].x) * (p[i].x - p[j].x) + (p[i].y - p[j].y) * (p[i].y - p[j].y));
    }
}
double dis[maxn];
double prim(double l) {
    mem(vis, 0);
    for (int i = 2; i <= n; i++) {
        dis[i] = abs(p[i].z - p[1].z) - edge[1][i] * l;
        pre[i] = 1;
    }
    vis[1] = 1;
    double cost = 0;
    for (int i = 1; i < n; i++) {
        int k = -1;
        double mn = INF;
        for (int j = 1; j <= n; j++)
            if (!vis[j] && dis[j] < mn) {
                mn = dis[j];
                k = j;
            }
        if (k != -1) {
            vis[k] = 1;
            cost += dis[k];
            for (int j = 1; j <= n; j++)
                if (!vis[j]) {
                    double val = abs(p[k].z - p[j].z) - edge[k][j] * l;
                    if (dis[j] > val) {
                        dis[j] = val;
                        pre[j] = k;
                    }
                }
        }
    }
    return cost;
}
void binary() {
    double low = 0, high = 100.0, mid;
    while (high - low > eps) {
        mid = (high + low) / 2;
        if (prim(mid) >= 0)
            low = mid;
        else
            high = mid;
    }
    printf("%.3f\n", mid);
}
int main() {
    while (scanf("%d", &n) != EOF) {
        if (!n) break;
        init();
        binary();
    }
    return 0;
}

//迭代法
using namespace std;
int n, vis[maxn], pre[maxn];
struct node {
    int x, y, z;
} p[maxn];
double edge[maxn][maxn];
void init() {
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &p[i].x, &p[i].y, &p[i].z);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++)
            edge[i][j] = edge[j][i] = sqrt((p[i].x - p[j].x) * (p[i].x - p[j].x) + (p[i].y - p[j].y) * (p[i].y - p[j].y));
    }
}
double dis[maxn];
double prim(double l) {
    mem(vis, 0);
    for (int i = 2; i <= n; i++) {
        dis[i] = abs(p[i].z - p[1].z) - edge[1][i] * l;
        pre[i] = 1;
    }
    vis[1] = 1;
    double cost = 0, len = 0;
    for (int i = 1; i < n; i++) {
        int k = -1;
        double mn = INF;
        for (int j = 1; j <= n; j++)
            if (!vis[j] && dis[j] < mn) {
                mn = dis[j];
                k = j;
            }
        if (k != -1) {
            vis[k] = 1;
            cost += abs(p[k].z - p[pre[k]].z);
            len += edge[k][pre[k]];
            for (int j = 1; j <= n; j++)
                if (!vis[j]) {
                    double val = abs(p[k].z - p[j].z) - edge[k][j] * l;
                    if (dis[j] > val) {
                        dis[j] = val;
                        pre[j] = k;
                    }
                }
        }
    }
    return cost / len;
}
void iter() {
    double a = 0, b;
    while (1) {
        b = prim(a);
        if (fabs(a - b) < eps) break;
        a = b;
    }
    printf("%.3f\n", b);
}
int main() {
    while (scanf("%d", &n) != EOF) {
        if (!n) break;
        init();
        iter();
    }
    return 0;
}