// 所有下标从1开始，下标为0必须值为0

//二维树状数组

//单点更新，矩阵求和
ll C[N][N];
int n,m;//矩阵大小，全局变量
void update(int x,int y,ll c){ //需要手动初始化
  for(int i=x;i<=n;i+=i&(-i)) 
    for(int j=y;j<=m;j+=i&(-i))
      C[i][j] += c;
}
ll query(int x,int y){
  ll ans = 0;
  for(int i=x;i;i-=i&(-i)) 
    for(int j=y;j;j-=i&(-i))
      ans += C[i][j];
  return ans;
}
ll querys(int x1,int y1,int x2,int y2){
  return query(x2,y2) - query(x1-1,y2) - query(x2,y1-1) + query(x1-1,y1-1);
}

//矩阵更新，单点求和
ll C[N][N];
int n,m;//矩阵大小，全局变量
void update(int x,int y,ll c){ //需要手动初始化
  for(int i=x;i<=n;i+=i&(-i)) 
    for(int j=y;j<=m;j+=i&(-i))
      C[i][j] += c;
}
void updates(int x1,int y1,int x2,int y2,ll c){
  update(x1,y1,c);
  update(x1,y2+1,-c);
  update(x2+1,y1,-c);
  update(x2+1,y2+1,c);
}
ll query(int x,int y){
  ll ans = 0;
  for(int i=x;i;i-=i&(-i)) 
    for(int j=y;j;j-=i&(-i))
      ans += C[i][j];
  return ans;
}
void init(ll A[][N]){ //预处理，A下标从1开始
  // memset(C,0,sizeof C);
  for(int i=1;i<=n;++i)
    for(int j=1;j<=m;++i)
      update(i,j,A[i][j]-A[i-1][j]-A[i][j-1]+A[i-1][j-1]);
}


//矩阵更新，矩阵求和
ll C[4][N][N];
int n,m;//矩阵大小，全局变量
void update(int x,int y,ll c){ //需要手动初始化
  for(int i=x;i<=n;i+=i&(-i)) 
    for(int j=y;j<=m;j+=i&(-i)){
      C[0][i][j] += c;
      C[1][i][j] += x*c;
      C[2][i][j] += y*c;
      C[3][i][j] += x*y*c;
    }
}
void updates(int x1,int y1,int x2,int y2,ll c){
  update(x1,y1,c);
  update(x1,y2+1,-c);
  update(x2+1,y1,-c);
  update(x2+1,y2+1,c);
}
ll query(int x,int y){
  ll ans = 0;
  for(int i=x;i;i-=i&(-i)) 
    for(int j=y;j;j-=i&(-i))
      ans += (x + 1) * (y + 1) * C[0][i][j]
                - (y + 1) * C[1][i][j]
                - (x + 1) * C[2][i][j]
                + C[3][i][j];
  return ans;
}
ll querys(int x1,int y1,int x2,int y2){
  return query(x2,y2) - query(x1-1,y2) - query(x2,y1-1) + query(x1-1,y1-1);
}
void init(ll A[][N]){ //预处理，A下标从1开始
  // memset(C,0,sizeof C);
  for(int i=1;i<=n;++i)
    for(int j=1;j<=m;++i)
      update(i,j,A[i][j]-A[i-1][j]-A[i][j-1]+A[i-1][j-1]);
}
