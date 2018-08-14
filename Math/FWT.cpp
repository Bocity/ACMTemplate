void FWT_or(int *a, int opt) {
    for (int i = 1; i < N; i <<= 1)
        for (int p = i << 1, j = 0; j < N; j += p)
            for (int k = 0; k < i; ++k)
                if (opt == 1)
                    a[i + j + k] = (a[j + k] + a[i + j + k]) % MOD;
                else
                    a[i + j + k] = (a[i + j + k] + MOD - a[j + k]) % MOD;
}
void FWT_and(int *a, int opt) {
    for (int i = 1; i < N; i <<= 1)
        for (int p = i << 1, j = 0; j < N; j += p)
            for (int k = 0; k < i; ++k)
                if (opt == 1)
                    a[j + k] = (a[j + k] + a[i + j + k]) % MOD;
                else
                    a[j + k] = (a[j + k] + MOD - a[i + j + k]) % MOD;
}
void FWT_xor(int *a, int opt) {
    for (int i = 1; i < N; i <<= 1)
        for (int p = i << 1, j = 0; j < N; j += p)
            for (int k = 0; k < i; ++k) {
                int X = a[j + k], Y = a[i + j + k];
                a[j + k] = (X + Y) % MOD;
                a[i + j + k] = (X + MOD - Y) % MOD;
                if (opt == -1) a[j + k] = 1ll * a[j + k] * inv2 % MOD, a[i + j + k] = 1ll * a[i + j + k] * inv2 % MOD;
            }
}
void fwt(ll a[], int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    fwt(a, l, mid);
    fwt(a, mid + 1, r);
    int len = mid - l + 1;
    for (int i = l; i <= mid; ++i) {
        ll x1 = a[i];
        ll x2 = a[i + len];
        a[i] = x1 + x2;
        a[i + len] = x1 - x2;
    }
}
void ifwt(ll a[], int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    int len = mid - l + 1;
    for (int i = l; i <= mid; ++i) {
        ll y1 = a[i];
        ll y2 = a[i + len];
        a[i] = (y1 + y2) / 2;
        a[i + len] = (y1 - y2) / 2;
    }
    ifwt(a, l, mid);
    ifwt(a, mid + 1, r);
}