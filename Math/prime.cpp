#include <bits/stdc++.h>
using namespace std;
#define N 99999 // range to screen

typedef long long ll;

const int maxn=10000000+1;
int prime[maxn], tot = 0;
bool vis[maxn] = {true, true};
void screen() {
    for (int i = 2; i < maxn; i++) {
        if (!vis[i]) prime[tot++] = i;
        for (int j = 0; j < tot && (ll) i * prime[j] < maxn; j++) {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    }
}

// 计算x的因数个数
// 因数个数 = 质因数指数+1 的 积
// O(tot)，tot为小于x的素数个数
// 因数不超过 2^px，px为素数连乘<=x的最大的长度
ll count(ll x){
  ll ans=1;
  for(int i=0;i<tot && prime[i] <= x && x>1;++i){
    if(x%prime[i] == 0){
      ll a=0;
      while(x%prime[i]==0) x/=prime[i],a++;
      ans *= (a+1);
    }
  }
  if (x>1) ans *= 2;
  return ans;
}

// 分解因数，O( sqrt(n) )
// n<1e14的因数不超过1e4个

ll fct[N];
int tot =0;
void getFactor(ll x){
    for(int i=1;(ll)i*i<=x;++i){
        if (x%i==0) fct[tot++] = i;
    }
    int tmp = fct[tot-1]*fct[tot-1] == x ? tot-1:tot;
    llp(i,0,tmp) fct[tot+tmp-1-i] = x/fct[i];
    tot += tmp;
}

int main() {
    screen();
    cout << prime[3000 - 1] << endl; // 3000th prime
}