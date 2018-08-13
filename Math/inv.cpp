//递推逆元，O(n)
ll inv[N];
void getInv(int n,ll mod = MOD){
    inv[1] = 1;
    for (int i = 2; i <= n; i++) inv[i] = inv[mod % i] * (mod - mod / i) % mod;
}

//求单个逆元，O(log n)
ll getInv(ll n,ll mod = MOD) {
    return qpower(n, mod - 2);
}

//阶乘和阶乘的逆元, O(n)
ll fac[N];
ll inv[N];
void getFac(int n) {
    fac[0] = 1;
    llp(i, 1, n + 1) fac[i] = fac[i - 1] * i % MOD;
    inv[n] = getInv(fac[n]);
    rlp(i, 0, n) inv[i] = (i + 1) * inv[i + 1] % MOD;
}