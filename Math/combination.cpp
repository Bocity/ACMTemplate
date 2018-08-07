// -------------------- n > 1e6, m <=1e6--------------------------
// 直接递推。记住，组合数计算复杂度只和m有关
// C(n,m) = n*n-1*...*n-m+1 * inv[m]
ll fac[N];
ll inv[N];
void getFac(int n) {
    fac[0] = 1;
    llp(i, 1, n + 1) fac[i] = fac[i - 1] * i % MOD;
    inv[n] = getInv(fac[n]);
    rlp(i, 0, n) inv[i] = (i + 1) * inv[i + 1] % MOD;
}
ll C(ll n,ll m){
    m = min(n-m,m);
    ll ans=1;
    for(int i=0;i<m;++i) ans = (n-i)%MOD*ans%MOD;  // >1e9的数在乘之前需要先取模
    ans = ans*inv[m]%MOD;
    return ans;
} 
//C(1000000000000000000,2) = 1176
//s.p. 当n=1e18, m>=50时 C%(1e9+7) = 0，因为1e18-49是1e9+7的倍数。。。

// -------------------- n <= 1e6 --------------------------

// O(n)处理阶乘和逆元，直接计算C(n,m) = fac[n]*inv[n-m]*inv[m]
// 可以在O(n)的预处理下应付 n <= 1e6 的所有情况
// 但是取模常数较大，n固定情况下可用递推预处理
ll fac[N];
ll inv[N];
void getFac(int n) {
    fac[0] = 1;
    llp(i, 1, n + 1) fac[i] = fac[i - 1] * i % MOD;
    inv[n] = getInv(fac[n]);
    rlp(i, 0, n) inv[i] = (i + 1) * inv[i + 1] % MOD;
}
ll C(int n,int m){
    return fac[n]*inv[n-m]%MOD*inv[m]%MOD;
}

// O(n) 递推 C(n,0)->C(n,n)
ll C[N];
void getCom(int n) {
    C[0] = 1;
    for (int i = 1; i <= n; i++) {
        C[i] = C[i - 1] * (n - i + 1) / i % MOD;
    }
}

// -------------------- n <= 1e3 --------------------------

// O(n^2) 递推 C(0,0)->C(n,n)
ll C[N][N];
void getCom(int n) {
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }
}