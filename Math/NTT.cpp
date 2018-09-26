// 是这样的，这几天在写 FFT，由于是在模意义下的，需要各种素数……

// 然后就打了个表方便以后查了、

// 如果 r⋅2k+1 是个素数，那么在modr⋅2k+1意义下，可以处理 2k 以内规模的数据，

// 2281701377=17⋅227+1 是一个挺好的数，平方刚好不会爆 long long

// 1004535809=479⋅221+1 加起来刚好不会爆 int 也不错

// 还有就是 998244353=119⋅223+1
// 下面是刚刚打出来的表格（g 是mod(r⋅2k+1)的原根）

// r⋅2k+1	r	k	g
// 3	1	1	2
// 5	1	2	2
// 17	1	4	3
// 97	3	5	5
// 193	3	6	5
// 257	1	8	3
// 7681	15	9	17
// 12289	3	12	11
// 40961	5	13	3
// 65537	1	16	3
// 786433	3	18	10
// 5767169	11	19	3
// 7340033	7	20	3
// 23068673	11	21	3
// 104857601	25	22	3
// 167772161	5	25	3
// 469762049	7	26	3
// 998244353	119	23	3
// 1004535809	479	21	3
// 2013265921	15	27	31
// 2281701377	17	27	3
// 3221225473	3	30	5
// 75161927681	35	31	3
// 77309411329	9	33	7
// 206158430209	3	36	22
// 2061584302081	15	37	7
// 2748779069441	5	39	3
// 6597069766657	3	41	5
// 39582418599937	9	42	5
// 79164837199873	9	43	5
// 263882790666241	15	44	7
// 1231453023109121	35	45	3
// 1337006139375617	19	46	3
// 3799912185593857	27	47	5
// 4222124650659841	15	48	19
// 7881299347898369	7	50	6
// 31525197391593473	7	52	3
// 180143985094819841	5	55	6
// 1945555039024054273	27	56	5
// 4179340454199820289	29	57	3
#include <bits/stdc++.h>
#define RG register
#define IL inline
#define Fill(a, b) memset(a, b, sizeof(a))
using namespace std;
typedef long long ll;
const int Zsy(998244353);
const int Phi(998244352);
const int G(3);
const int _(4e5 + 5);

IL ll Input() {
    RG ll x = 0, z = 1;
    RG char c = getchar();
    for (; c < '0' || c > '9'; c = getchar()) z = c == '-' ? -1 : 1;
    for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
    return x * z;
}

int n, m, N, l, r[_], A[_], B[_];

IL int Pow(RG ll x, RG ll y) {
    RG ll ret = 1;
    for (; y; y >>= 1, x = x * x % Zsy)
        if (y & 1) ret = ret * x % Zsy;
    return ret;
}

IL void NTT(RG int *P, RG int opt) {
    for (RG int i = 0; i < N; ++i)
        if (r[i] < i) swap(P[r[i]], P[i]);
    for (RG int i = 1; i < N; i <<= 1) {
        RG int W = Pow(G, Phi / (i << 1));
        if (opt == -1) W = Pow(W, Zsy - 2);
        for (RG int j = 0, p = i << 1; j < N; j += p) {
            RG int w = 1;
            for (RG int k = 0; k < i; ++k, w = 1LL * w * W % Zsy) {
                RG int X = P[k + j], Y = 1LL * w * P[k + j + i] % Zsy;
                P[k + j] = (X + Y) % Zsy, P[k + j + i] = (X - Y + Zsy) % Zsy;
            }
        }
    }
}

int main(RG int argc, RG char *argv[]) {
    n = Input(), m = Input();
    for (RG int i = 0; i <= n; ++i) A[i] = Input();
    for (RG int i = 0; i <= m; ++i) B[i] = Input();
    for (n += m, N = 1; N <= n; N <<= 1) ++l;
    for (RG int i = 0; i < N; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
    NTT(A, 1);
    NTT(B, 1);
    for (RG int i = 0; i < N; ++i) A[i] = 1LL * A[i] * B[i] % Zsy;
    NTT(A, -1);
    RG int inv = Pow(N, Zsy - 2);
    for (RG int i = 0; i <= n; ++i) printf("%lld ", 1LL * A[i] * inv % Zsy);
    return 0;
}
