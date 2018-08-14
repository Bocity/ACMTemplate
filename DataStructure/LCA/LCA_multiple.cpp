// 模板题：hdu 2586

#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
using namespace std;

typedef long long ll;

const int N = 40050;

int depth[N];

int f[N][20]; // f数组
ll dir[N]; // 每个点到根结点的路径长度

struct edge{
  int to;
  int w;
};
vector<edge> E[N];//邻接表存图

bool used[N];
void dfs(int u){ //预处理dfs
  used[u] = true; 
  for(int i=1;i<=15;++i){
    f[u][i] = f[ f[u][i-1] ][i-1]; //计算f数组
  }

  for(edge e:E[u])
    if (!used[e.to]){ 
      depth[e.to] = depth[u]+1;
      f[e.to][0] = u; // f初值即为父亲结点
      dir[e.to] = dir[u] + e.w;
      dfs(e.to);
    }
}

int LCA(int u,int v){
  if (depth[u] < depth[v]) swap(u,v);// 1.若u高于v，交换。使u低于v。

  for(int i=15;i>=0;--i) // 2.使u爬到和v一样高
    if (depth[ f[u][i] ] >= depth[v]) // 若f[u][i]不高于v则向上爬
      u = f[u][i];
      
  if (u == v) return u;// u为v的子结点的情况

  for(int i=15;i>=0;--i) // 3.同步倍增
    if (f[u][i] != f[v][i]) {
      u = f[u][i];
      v = f[v][i];
    }
  
  return f[u][0]; // u和v在不同子树上的情况, 此时必有f[u][0] = f[v][0] = lca
}

int main(){
  // std::ios::sync_with_stdio(false);

  int n,m;
  int t;scanf("%d",&t);
  while(scanf("%d%d",&n,&m) != EOF){
    // 读入数据
    for(int i=0;i<=n;++i) {
      vector<edge>().swap(E[i]);
    }
    int o,p,q;
    for(int i=0;i<n-1;++i){
      scanf("%d%d%d",&o,&p,&q);
      E[o].push_back({p,q});
      E[p].push_back({o,q});
    } 
    // 预处理
    memset(used,0,sizeof used);
    depth[1] = 0; // 根结点的depth
    f[1][0] = 0; // 根结点的f, 所有f的越界值都为根结点的f
    dir[1] = 0;
    dfs(1); 
    // 在线处理询问 
    for(int i=0;i<m;++i){
      scanf("%d%d",&o,&p);
      int lca = LCA(o,p); 
      printf("%lld\n",dir[p]+dir[o]-2*dir[lca]);
    }
  }
}
