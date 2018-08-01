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
// O(n) 递推 C(n,0)->C(n,n)
ll C[N];
void getCom(int n) {
    C[0] = 1;
    for (int i = 1; i <= n; i++) {
        C[i] = C[i - 1] * (n - i + 1) / i % MOD;
    }
}