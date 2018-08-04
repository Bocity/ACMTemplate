// pbds版
#include <ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
#define param ll, less<ll>, binomial_heap_tag
__gnu_pbds::priority_queue<param> pq[N];
int f[N]; //记录是否在同一集合，并查集实现
int fd(int x) {
    if (x == f[x]) return f[x];
    return f[x] = fd(f[x]);
}
//合并
int fx = fd(i);
int fy = fd(j);
if (fx != fy) {
    pq[fx].join(pq[fy]);
    f[fy] = fx;
}
//删除
fx = fd(i) pq[fx].pop();

//手写版  较快，省内存，左偏树实现
struct heap {
    int l, r, dis;
    ll v;
} tr[N];
inline int merge(int x, int y) { //返回合并后根编号
    if (!x || !y) return x + y;
    if ((tr[x].v < tr[y].v) || (tr[x].v == tr[y].v && x > y)) swap(x, y);
    tr[x].r = merge(tr[x].r, y);
    f[tr[x].r] = x;
    if (tr[tr[x].l].dis < tr[tr[x].r].dis) swap(tr[x].l, tr[x].r);
    if (!tr[x].r)
        tr[x].dis = 0;
    else
        tr[x].dis = tr[tr[x].r].dis + 1;
    return x;
}
inline int pop(int x) { //返回删除后根编号
    int L = tr[x].l,R = tr[x].r;
    f[L] = L;
    f[R] = R;
    tr[x].dis = tr[x].l = tr[x].r = 0;
    return merge(L, R);
}

// 合并
int fx = fd(i); //并查集   //解决冲突  若保证没有冲突可以删掉
int fy = fd(j);
if (fx != fy) {
    fx = merge(fx, fy);
}
fx = pop(fx);