//求单个欧拉函数，O(sqrt(n))
int oula(int n)
{
    int rea=n;
    for(int i=2; i*i<=n; i++)
        if(n%i==0)//第一次找到的必为素因子
        {
            rea=rea-rea/i;
            do
                n/=i;//把该素因子全部约掉
            while(n%i==0);
        }
    if(n>1)
        rea=rea-rea/n;
    return rea;
}

// [1,maxn)
const int maxn = 10001;
int phi[maxn];
bool vis[maxn] = {true, true};
int prime[maxn];
int tot=0;
void phi_table(int n) {
    tot = 0;
    phi[1] = 1;
    for (int i = 2; i < maxn; i++) {
        if (!vis[i]) {
            prime[tot++] = i;
            phi[i] = i - 1;
        }
        for (int j = 0; j < tot && (ll) i * prime[j] < maxn; j++) {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            } else {
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            }
        }
    }
}