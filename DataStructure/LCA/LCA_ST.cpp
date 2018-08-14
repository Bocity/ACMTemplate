// 模板题：hdu 2586

#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

typedef long long ll;

const int N = 40050;

struct edge{
  int to;
  int w;
};
vector<edge> E[N];//邻接表存图

int L[2*N]; // 欧拉序列
int depth[2*N]; // 深度序列
int pos[N]; // 首位置序列
int tot; // 序列顶指针

ll dir[N]; // 每个点到根结点的路径长度

bool used[N];
void dfs(int u, int dep) { // 得到树的欧拉序列、深度序列和首位置序列
    used[u] = true;
    pos[u] = tot;

    L[tot] = u;
    depth[tot] = dep;
    ++tot;
    for(edge e:E[u])
      if (!used[e.to]){
        dir[e.to] = dir[u] + e.w;
        dfs(e.to,dep+1);
        L[tot] = u;
        depth[tot] = dep;
        ++tot;
      }
}
 
int Min(int x,int y){ // 根据情况修改     
  return depth[x] < depth[y] ? x:y;
}
int f[2*N][20]; // f数组
void ST(int n) {
  for(int i = 0;i<n;++i) f[i][0] = i; // f初始值即为自身下标     //下标从0开始

  for(int j = 1;j<=log2(n);++j) // DP
    for (int i = 0;i + (1<<j) <= n;++i){ // 为了防止越界。实际上 i+2^j > n 时，是不会被查询到的。
      f[i][j] = Min(f[i][j-1], f[i + (1 << (j-1))][j-1]); // f维护的是区间内深度最小的下标
    }
}
int RMQ(int l, int r) { 
    int t = log2(r-l+1);
    return Min(f[l][t], f[r - (1 << t) + 1][t]);
}
int LCA(int u, int v) { // LCA(T,u,v) = RMQ(L,pos[u],pos[v])
    if (pos[u] > pos[v]) swap(u, v);
    return L[RMQ(pos[u], pos[v])];
}

int main(){
  // std::ios::sync_with_stdio(false);
  int n,m;
  int t;scanf("%d",&t);
  while(scanf("%d%d",&n,&m) != EOF){
    //邻接表初始化
    for(int i=0;i<=n;++i) {
      vector<edge>().swap(E[i]);
    }
    // 读入数据
    int o,p,q;
    for(int i=0;i<n-1;++i){
      scanf("%d%d%d",&o,&p,&q);
      E[o].push_back({p,q});
      E[p].push_back({o,q});
    } 
    // 预处理
    tot = 0;
    dir[1] = 0;
    memset(used,0,sizeof used);
    dfs(1,0);
    ST(tot); // tot == 2*n-1
    // 在线处理询问O(1)
    for(int i=0;i<m;++i){
      scanf("%d%d",&o,&p);
      int lca = LCA(o,p); 
      printf("%lld\n",dir[p]+dir[o]-2*dir[lca]);
    }
  }
}
