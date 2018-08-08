// 区间求和

// 线段树区间更新
#define LSON l, m, rt << 1
#define RSON m + 1, r, rt << 1 | 1
#define lson rt << 1
#define rson rt << 1 | 1
ll ans[N << 2], lazy[N << 2];
// 更新答案，需要修改
inline void Maintain(const int &rt) { 
    ans[rt] = ans[lson] + ans[rson];
    return;
}
// 延时标记下传，需要修改
inline void Pushdown(const int &rt, const int &m) {
    if (lazy[rt] != 0) { // lazy更新，需要修改
        lazy[rt << 1] += lazy[rt];
        lazy[rt << 1 | 1] += lazy[rt];
        ans[rt << 1] += lazy[rt] * (m - (m >> 1));
        ans[rt << 1 | 1] += lazy[rt] * (m >> 1);
        lazy[rt] = 0;
    }
}
void build(int l, int r, const int &rt = 1) {
    lazy[rt] = 0; // lazy数组初值为0
    if (l == r) {
        ans[rt] = a[rk[l]];  // 线段树初始值，需要修改
        return;
    }
    int m = (l + r) >> 1;
    build(LSON);
    build(RSON);
    Maintain(rt);
    return;
}
void update(const int &L,const int &R, const ll &c, int l, int r,const int &rt = 1) {
    if (L <= l && r <= R) {  // 区间更新，需要修改
        lazy[rt] += c;
        ans[rt] += c * (r - l + 1);
        return;
    }
    Pushdown(rt, r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m) update(L, R, c, LSON);
    if (m < R) update(L, R, c, RSON);
    Maintain(rt);
    return;
}
ll query(const int &L,const int &R, int l, int r,const int &rt = 1) {
    if (L <= l && r <= R) { 
        return ans[rt];
    }
    Pushdown(rt, r - l + 1);
    int m = (l + r) >> 1;
    ll ret = 0;  //  统计答案，需要修改
    if (L <= m) ret += query(L, R, LSON);
    if (m < R) ret += query(L, R, RSON);
    return ret;
}


// 区间最值


// 线段树区间更新
#define LSON l, m, rt << 1
#define RSON m + 1, r, rt << 1 | 1
#define lson rt << 1
#define rson rt << 1 | 1
ll ans[N << 2], lazy[N << 2];
// 更新答案，需要修改
inline void Maintain(const int &rt) { 
    ans[rt] = max(ans[lson] , ans[rson]);
    return;
}
// 延时标记下传，需要修改
inline void Pushdown(const int &rt) {
    if (lazy[rt] != 0) { // lazy更新，需要修改
        lazy[rt << 1] += lazy[rt];
        lazy[rt << 1 | 1] += lazy[rt];
        ans[rt << 1] += lazy[rt];
        ans[rt << 1 | 1] += lazy[rt];
        lazy[rt] = 0;
    }
}
void build(int l, int r, const int &rt = 1) {
    lazy[rt] = 0; // lazy数组初值为0
    if (l == r) {
        ans[rt] = a[l];  // 线段树初始值，需要修改
        return;
    }
    int m = (l + r) >> 1;
    build(LSON);
    build(RSON);
    Maintain(rt);
    return;
}
void update(const int &L,const int &R,cosnt ll &c, int l, int r,const int &rt = 1) {
    if (L <= l && r <= R) {  // 区间更新，需要修改
        lazy[rt] += c;
        ans[rt] += c;
        return;
    }
    Pushdown(rt);
    int m = (l + r) >> 1;
    if (L <= m) update(L, R, c, LSON);
    if (m < R) update(L, R, c, RSON);
    Maintain(rt);
    return;
}
ll query(const int &L,const int &R, int l, int r,const int &rt = 1) {
    if (L <= l && r <= R) { 
        return ans[rt];
    }
    Pushdown(rt);
    int m = (l + r) >> 1;
    ll ret = 0;  //  统计答案，需要修改
    if (L <= m) ret = max(ret,query(L, R, LSON));
    if (m < R)  ret = max(ret,query(L, R, RSON));
    return ret;
}

