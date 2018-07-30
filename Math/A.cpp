#include<bits/stdc++.h>
using namespace std;

#define llp(i,x,y) for(int i=x;i<y;++i) // [x,y) x->y
#define REP llp
#define rlp(i,x,y) for(int i=y-1;i>=x;--i)  // [x,y) y->x
#define PER rlp
#define lp(i,x) for(int i=0;i<x;++i) //[0,x）0->x
#define mem(a,x) memset(a,x,sizeof a)
#define endl "\n"

typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<int,int> pii;
// typedef __int128 ull;
typedef unsigned long long ull;

#define fi first
#define se second
#define pb push_back

const ll MOD=1e9+7;
const ll N=1e5+50;
const db eps=1e-9;

inline ll qpower(ll x,ll p,ll M=MOD){ll ans=1;while(p){if (p&1) ans=ans*x%M;p>>=1;x=x*x%M;}return ans;}
inline ll gcd(ll a,ll b){ll x;while(b){x = a%b;a = b;b = x;}return a;}
inline ll modp(ll x,ll p = MOD){return (x%p+p)%p;}
inline void addp(ll& x,ll y,ll p = MOD){x += y;if (x>=MOD) x-=MOD;}
inline int ifloor(db x){return x>0?int(x+eps):int(x-eps);}
// std::ios::sync_with_stdio(false);
// srand((unsigned)time(NULL));
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
int main(){
  phi_table2(10000);
  llp(i,2,1000) cout<<phi[i]<<" ";
}