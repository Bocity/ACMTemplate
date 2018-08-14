ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    ll ret = exgcd(b, a % b, x, y), tmp = y;
    y = x - a / b * y;
    x = tmp;
    return ret;
}
ll inv(ll a, ll mod) {
    ll x, y;
    ll gcd = exgcd(a, mod, x, y);
    if (gcd != 1) return -1;
    return x < 0 ? x + mod : x;
}
struct modeq {
    ll a, mod;
    modeq() {}
    modeq(ll a, ll mod)
        : a(a)
        , mod(mod) {}

    modeq crt(const modeq &p) const { // 保证所有运算在 lcm + max(p.moder, moder) 的数据范围内实现，注意不要让模数为 0
        modeq p1 = *this, p2 = p;
        if (p1.mod < p2.mod) std::swap(p1, p2);
        ll x, y;
        ll gcd = exgcd(p1.mod, p2.mod, x, y);
        if ((p2.a - p1.a) % gcd) return modeq(0, 0); //mod 为0无解
        ll lcm = p1.mod / gcd * p2.mod;
        ll ans = (p2.a - p1.a) / gcd;
        ans = 1ll * ans * x % (p2.mod / gcd) * p1.mod;
        ans += p1.a;
        ans += ans < 0 ? lcm : ans >= lcm ? -lcm : 0;
        return modeq(ans, lcm);
    }
};
