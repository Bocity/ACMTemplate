/*全局最小割
大致是来解决这样一类问题：
给定一个n个点m条边的无向图，每条边有一个最大流量，给定一个源点s，求以哪个点作为汇点可以使整个图的最大流最小。
O(n^3)
*/
int map[maxn][maxn];
int n;
void contract(int x,int y) {
  int i,j;
  for (i=0; i<n; i++)
    if (i!=x) map[x][i]+=map[y][i],map[i][x]+=map[i][y];
  for (i=y+1; i<n; i++) for (j=0; j<n; j++) {
      map[i-1][j]=map[i][j];
      map[j][i-1]=map[j][i];
    }
  n--;
}
int w[maxn],c[maxn];
int sx,tx;
int mincut() {
  int i,j,k,t;
  memset(c,0,sizeof(c));
  c[0]=1;
  for (i=0; i<n; i++) w[i]=map[0][i];
  for (i=1; i+1<n; i++) {
    t=k=-1;
    for (j=0; j<n; j++) if (c[j]==0&&w[j]>k)
        k=w[t=j];
    c[sx=t]=1;
    for (j=0; j<n; j++) w[j]+=map[t][j];
  }
  for (i=0; i<n; i++) if (c[i]==0) return w[tx=i];
}
int main() {
  int i,j,k,m;
  while (scanf("%d%d",&n,&m)!=EOF) {
    memset(map,0,sizeof(map));
    while (m--) {
      scanf("%d%d%d",&i,&j,&k);
      map[i][j]+=k;
      map[j][i]+=k;
    }
    int mint=999999999;
    while (n>1) {
      k=mincut();
      if (k<mint) mint=k;
      contract(sx,tx);
    }
    printf("%d\n",mint);
  }
  return 0;
}
