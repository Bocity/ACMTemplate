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

const int maxx = 2e7 + 5;
int phi[maxx];
bool check[maxx];
int prime[maxx];
void phi_table2(int n) { //线性筛改
    phi[1] = 1;
    int tot = 0;
    for (int i = 2; i <= n; i++) {
        if (!check[i]) {
            prime[tot++] = i;
            phi[i] = i - 1;
        }
        for (int j = 0; j < tot; j++) {
            if (i * prime[j] > n) break;
            check[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            } else {
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            }
        }
    }
}