#include <bits/stdc++.h>
#define eps 1e-8
using namespace std;
struct point {
    double x, y;
} p[100005], o;
int n;
double r;
inline double sqr(double x) {
    return x * x;
}
inline double dis(point a, point b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
inline bool cmp(double a, double b) {
    return fabs(a - b) < eps;
}
point geto(point a, point b, point c) {
    double a1, a2, b1, b2, c1, c2;
    point ans;
    a1 = 2 * (b.x - a.x), b1 = 2 * (b.y - a.y), c1 = sqr(b.x) - sqr(a.x) + sqr(b.y) - sqr(a.y);
    a2 = 2 * (c.x - a.x), b2 = 2 * (c.y - a.y), c2 = sqr(c.x) - sqr(a.x) + sqr(c.y) - sqr(a.y);
    if (cmp(a1, 0)) {
        ans.y = c1 / b1;
        ans.x = (c2 - ans.y * b2) / a2;
    } else if (cmp(b1, 0)) {
        ans.x = c1 / a1;
        ans.y = (c2 - ans.x * a2) / b2;
    } else {
        ans.x = (c2 * b1 - c1 * b2) / (a2 * b1 - a1 * b2);
        ans.y = (c2 * a1 - c1 * a2) / (b2 * a1 - b1 * a2);
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> p[i].x >> p[i].y;
    }
    random_shuffle(p + 1, p + n + 1);
    o = p[1];
    for (int i = 2; i <= n; ++i) {
        if (dis(o, p[i]) < r ) continue;
        o = p[i];
        r = 0;
        for (int j = 1; j < i; ++j) {
            if (dis(o, p[j]) < r) continue;
            o.x = (p[i].x + p[j].x) / 2;
            o.y = (p[i].y + p[j].y) / 2;
            r = dis(p[i], p[j]) / 2;
            for (int k = 1; k < j; ++k) {
                if (dis(o, p[k]) < r ) continue;
                o = geto(p[i], p[j], p[k]);
                r = dis(o, p[i]);
            }
        }
    }
    cout << fixed << setprecision(10) << r << endl;
    cout << fixed << setprecision(10) << o.x << " " << o.y << endl;
}
