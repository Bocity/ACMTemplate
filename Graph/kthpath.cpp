// #pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;

#define llp(i,x,y) for(int i=x;i<y;++i) // [x,y) x->y
#define rlp(i,x,y) for(int i=y-1;i>=x;--i)  // [x,y) y->x
#define mem(a,x) memset(a,x,sizeof a)

typedef long long ll;

const ll MOD=1e9+7;
const ll N=1e6+50;
const ll INF=2e18;

ll qpower(ll x,ll p,ll M=MOD){ll ans=1;while(p){if (p&1) ans=ans*x%M;p>>=1;x=x*x%M;}return ans;}
ll gcd(ll a,ll b){ll x;while(b){x = a%b;a = b;b = x;}return a;}

ll modp(ll x,ll p = MOD){return (x%p+p)%p;} //常数较大
ll addp(ll x,ll y,ll p = MOD){return x+y>=p?x+y-p:x+y;}
ll subp(ll x,ll y,ll p = MOD){return x-y<0?x-y+p:x-y;}

typedef unsigned long long ull;
// typedef __int128 ull;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back


int K;
class states {
public:
  int cost,id;
};
int dist[1000];
class cmp {
public:
  bool operator ()(const states &i,const states &j) {
    return i.cost>j.cost;
  }
};
class cmp2 {
public:
  bool operator ()(const states &i,const states &j) {
    return i.cost+dist[i.id]>j.cost+dist[j.id];
  }
};
struct edges {
  int to,next,cost;
} edger[100000],edge[100000];
int headr[1000],head[1000],Lr,L;
void dijkstra(int s) {
  states u;
  u.id=s;
  u.cost=0;
  dist[s]=0;
  priority_queue<states,vector<states>,cmp> q;
  q.push(u);
  while (!q.empty()) {
    u=q.top();
    q.pop();
    if (u.cost!=dist[u.id]) continue;
    for (int i=headr[u.id]; i!=-1; i=edger[i].next) {
      states v=u;
      v.id=edger[i].to;
      if (dist[v.id]>dist[u.id]+edger[i].cost) {
        v.cost=dist[v.id]=dist[u.id]+edger[i].cost;
        q.push(v);
      }
    }
  }
}
int num[1000];
void init(int n) {
  Lr=L=0;
  memset(head,-1,4*n);
  memset(headr,-1,4*n);
  memset(dist,63,4*n);
  memset(num,0,4*n);
}
void add_edge(int u,int v,int x) {
  edge[L].to=v;
  edge[L].cost=x;
  edge[L].next=head[u];
  head[u]=L++;
  edger[Lr].to=u;
  edger[Lr].cost=x;
  edger[Lr].next=headr[v];
  headr[v]=Lr++;
}
int a_star(int s,int t) {
  if (dist[s]==0x3f3f3f3f)
    return -1;
  priority_queue<states,vector<states>,cmp2> q;
  states tmp;
  tmp.id=s;
  tmp.cost=0;
  q.push(tmp);
  while (!q.empty()) {
    states u=q.top();
    q.pop();
    num[u.id]++;
    if (num[t]==K)
      return u.cost;
    for (int i=head[u.id]; i!=-1; i=edge[i].next) {
      int v=edge[i].to;
      tmp.id=v;
      tmp.cost=u.cost+edge[i].cost;
      q.push(tmp);
    }
  }
  return -1;
}
int main() {
  int n,m;
  scanf("%d%d",&n,&m);
  init(n);
  for (int i=0; i<m; i++) {
    int u,v,x;
    scanf("%d%d%d",&u,&v,&x);
    add_edge(u-1,v-1,x);
  }
  int s,t;
  scanf("%d%d%d",&s,&t,&K);
  if (s==t)
    K++;
  dijkstra(t-1);
  printf("%d\n",a_star(s-1,t-1));
}

