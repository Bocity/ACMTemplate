ll powMod(ll a, ll b) {
    if (a < 30) return Mod(1 << a, b);
    if (b <= 1000000)
        return b;
    else
        return qpower(2, a, b) + b;
}
ll dfs(int p) {
    if (p == 1) return 0;
    int phip = phi(p);   //记忆化
    return qpow(2, f(phip) + phip, p);
}