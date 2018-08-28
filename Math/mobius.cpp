//单个
int mobi(int n) {
    int m = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            m *= -1;
            int k = 0;
            do {
                k++;
                if (k > 1) {
                    m = 0;
                    break;
                }
                n /= i;
            } while (n % i == 0);
        }
    }
    if (n > 1) m *= -1;
    return m;
}
//线性筛求mu, [1,maxn)
const int maxn = 10000+1;
int mu[maxn];
bool vis[maxn] = {true, true};
int prime[maxn];
int tot=0;
void init() {
    memset(vis, 0, sizeof(vis));
    mu[1] = 1;
    tot = 0;
    for (int i = 2; i < maxn; i++) {
        if (!vis[i]) {
            prime[tot++] = i;
            mu[i] = -1;
        }
        for (int j = 0; j < tot && (ll) i * prime[j] < maxn; j++) {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            } else {
                mu[i * prime[j]] = -mu[i];
            }
        }
    }
    return;
}
