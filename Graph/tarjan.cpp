struct edge{
    int v,w,nxt;
};
const int N = 10000;//nodes
const int M = 100000;//edges

struct Tarjan {
    int dfn[N],low[N],tsp,id[N],cnt;
    int ins[N],s[N],top;
    edge e[2 * M];
    int pre[N],mcnt;
    void init() { 
        mem(pre, -1);mcnt = 0;
        mem(dfn,0);tsp=0;
        cnt=0;
        mem(ins,0);top=0;
    }
    void addarc(int x, int y, int z=0) {
        e[mcnt] = (edge){y, z, pre[x]}, pre[x]=mcnt++;
    }
    void tarjan(int u){
      s[top++]=u;ins[u]=1;
      low[u]=dfn[u]=++tsp;
      int v;
      for(int i=pre[u]; ~i; i=e[i].nxt){
          v=e[i].v;
          if(!dfn[v]) tarjan(v),low[u]=min(low[u], low[v]);
          else if(ins[v]) low[u]=min(low[u], dfn[v]);
      }
      if(low[u]==dfn[u]){
          ++cnt;
          do{
              v=s[--top];
              ins[v]=0;
              id[v]=cnt;
          }while(u!=v);
      }
    }
    int go(int n){
      for(int i=1;i<=n;i++) if (!dfn[i]) tarjan(i);
      return cnt;
    }
} solver;