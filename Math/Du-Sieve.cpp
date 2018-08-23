ll Smu(ll x) {
    if (x < maxn) return g[x];
    if (M[x]) return M[x];
    ll ans = 1;
    for (ll l = 2, r; l <= x; l = r + 1) {
        r = x / (x / l);
        ans -= (r - l + 1) * Smu(x / l);
    }
    return M[x] = ans;
}