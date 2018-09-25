// #pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;

#define llp(i,x,y) for(int i=x;i<y;++i) // [x,y) x->y
#define rlp(i,x,y) for(int i=y-1;i>=x;--i)  // [x,y) y->x
#define mem(a,x) memset(a,x,sizeof a)

typedef long long ll;
typedef unsigned long long ull;

const ll MOD=1e9+7;
const ll N=1e6+50;
const ll INF=2e18;

ll qpower(ll x,ll p,ll M=MOD){ll ans=1;while(p){if (p&1) ans=ans*x%M;p>>=1;x=x*x%M;}return ans;}
ll gcd(ll a,ll b){ll x;while(b){x = a%b;a = b;b = x;}return a;}

ll modp(ll x,ll p = MOD){return (x%p+p)%p;} //常数较大
ll addp(ll x,ll y,ll p = MOD){return x+y>=p?x+y-p:x+y;}
ll subp(ll x,ll y,ll p = MOD){return x-y<0?x-y+p:x-y;}

const double eps=1e-9;
int ifloor(double x){return x>0?int(x+eps):int(x-eps);}//浮点数注意精度误差
bool fequal(double x,double y){return fabs(x-y) <= eps; }

typedef unsigned long long ull;
// typedef __int128 ull;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back

// std::ios::sync_with_stdio(false);
// srand((unsigned)time(NULL));

int main(){
  ull x,y,z;
  x = 1231241241;
  z = 0;
  cout<<~x<<endl;
  cout<<z-1-x<<endl;
  cout<<z-1-x<<endl; 
}

/* 提交之前注意：
- 输入>1e6?上挂
- 溢出：会炸int的地方开了int，>1e9的数没取模?
- 多组输入输出？初始化了吗？
*/

/* 常见bug
- 边界/初值
- ll%MOD*ll%MOD
- 初始化
- int*int? u*u = ull 
- int(double+eps)
- 特例, n=0
- getchar()
*/
