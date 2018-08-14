// 模板题：hdu 2586

#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
using namespace std;

typedef long long ll;

const int N = 40050;

struct edge{
  int to;
  int w;
};
vector<edge> E[N];

struct query{
  int to;//询问点
  int index;//询问序号
};
vector<query> Q[N];//query结构体存每个结点的询问序列，需要记录询问序号

int ans[500];//每个询问的答案

int dir[N]; // 每个点到根结点的路径长度

// 并查集
int fa[N];
int find(int x){ // 并查集路径压缩查询，接近O(1)
  if (fa[x] == x) return x;
  else return fa[x] = find(fa[x]);
}
void merge(int u,int v){ // 并查集合并, u的顶点合并到v的顶点
  fa[find(u)] = find(v);
}

bool used[N];
void tarjan(int u){ 
  used[u] = true; // 标记u已被访问
  //深搜
  for(edge e:E[u])
    if (!used[e.to]){ 
      dir[e.to] = dir[u]+e.w;
      tarjan(e.to);
      merge(e.to,u); //访问完子结点，合并子结点的并查集到自己，这里顺序不能反
    }
  //处理当前结点的所有询问
  for(query q:Q[u])
    if (used[q.to]){
      int lca = find(q.to);
      ans[q.index] = dir[u]+dir[q.to]-2*dir[lca];
    }
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
    //离线所有询问
    for(int i=0;i<m;++i){
      scanf("%d%d",&o,&p);
      Q[o].push_back({p,i});
      Q[p].push_back({o,i});
    }
    //处理所有询问
    for(int i=1;i<=n;++i) fa[i] = i;
    memset(used,0,sizeof used);
    dir[1] = 0;
    tarjan(1);
    //输出答案
    for(int i=0;i<m;++i) printf("%d\n",ans[i]);
  }
}
