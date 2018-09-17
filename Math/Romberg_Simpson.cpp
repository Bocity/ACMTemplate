#include <bits/stdc++.h>
#define REP(i, x, n) for (int i = (x); i < (n); ++i)
#define PER(i, x, n) for (int i = (n) -1; i >= x; --i)
#define endl "\n"
#define sqr(x) ((x) * (x))
#define eps 1e-8
#define PI acos(-1.0)
using namespace std;
typedef long long ll;
typedef long double ld;
const int maxn = 100;
ll n, m, k;
ld f(ld x) {
    return exp(-sqr(x));
}
int t1 = 0;
ld Romberg(ld a, ld b) {
    ld T1, T2, S1, S2, C1, C2, R1, R2, h,Rx = 0;
    int n = 1, k, m = 1;
    h = b - a;
    T1 = 0.5 * h * (f(b) + f(a));
    while (m <= maxn) {
        t1++;
        ld sum = 0.0;
        REP(k, 0, n) {
            ld x = a + (k + 0.5) * h;
            sum = sum + f(x);
        }
        n = n * 2, h = h * 0.5;
        T2 = 0.5 * (T1 + 2 * h * sum);
        S1 = (4 * T2 - T1) / 3;
        if (m == 1) {
            T1 = T2;
            ++m;
        } else {
            S2 = (4 * T2 - T1) / 3;
            C1 = (16 * S2 - S1) / 15;
            if (m == 2) {
                S1 = S2;
                T1 = T2;
                ++m;
            } else {
                S2 = (4 * T2 - T1) / 3;
                C2 = (16 * S2 - S1) / 15;
                if (m == 3) {
                    R1 = (64 * C2 - C1) / 63;
                    C1 = C2;
                    S1 = S2;
                    T1 = T2;
                    ++m;
                } else {
                    if (m >= 4) {
                        R2 = (64 * C2 - C1) / 63;
                        if (fabs(R2 - R1) < eps) break;
                        R1 = R2;
                        C1 = C2;
                        S1 = S2;
                        T1 = T2;
                        ++m;
                    }
                }
            }
        }
        if (fabs(R2 - Rx) < eps) break;
        Rx = R2;
    }
    return R2;
}
int t2 = 0;
ld Simpson(ld a, ld b) {
    ld fa = f(a);
    ld fb = f(b);
    ld h = b - a;
    ld T = h / 2.0 * (fa + fb);
    ld x, S1 = T, S2;
    ld T2;
    ld ep = eps + 1.0;
    int n = 1;
    while (ep >= eps) {
        t2++;
        ld p = 0.0;
        for (int k = 0; k <= n - 1; k++) {
            x = a + (k + 0.5) * h;
            p = p + (*f)(x);
        }
        T2 = (T + h * p) / 2.0;
        S2 = (4.0 * T2 - T) / 3.0;
        ep = fabs(S2 - S1);
        T = T2;
        S1 = S2;
        n = n * 2;
        h = h / 2.0;
    }
    return S2;
}
int main() {
    ios::sync_with_stdio(0);
    ld a, b;
    cin >> a >> b;
    cout << Romberg(a, b) << ":" << t1 << endl;
    cout << Simpson(a, b) << ":" << t2 << endl;
    return 0;
}
