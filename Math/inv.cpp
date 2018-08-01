//递推逆元，O(n)
int inv[N];
void getInv(int n,int mod = MOD){
    inv[1] = 1;
    for (int i = 2; i <= n; i++) inv[i] = inv[mod % i] * (mod - mod / i) % mod;
}

//求单个逆元，O(log n)
ll getInv(ll n,int mod = MOD) {
    return qpower(n, mod - 2);
}