ll A[N];
//树状数组维护前缀和。只维护C,不会使用A。
ll C[N];
int lowbit(int x){ // 返回最低位的1
  return -x&x; 
}
void update(int i,int x,int n){ //需要手动初始化
  for(;i<=n;i+=lowbit(i))
    C[i]+=x;
}
ll query(int i){
  ll ans = 0;
  for(;i;i-=lowbit(i)) //每次处理一个长度为lowbit(i)的区间
    ans += C[i];
  return ans;
}
void init(ll A[],int n){
  // memset(C,0,sizeof C);
  for(int i=1;i<=n;++i) update(i,A[i],n);
}

//树状数组维护区间最值，A[i]必须已经更新
ll C[N];
int lowbit(int x){ // 返回最低位的1
  return -x&x; // 原理：-x是取x的补码，即反码+1。二进制数加一时最低位的0成为1，更低的1都成为0。因此-x&x，最低位的1（反码中最低位的0）会保留下来，其他都会变成0，这样就得到了x的最低位的1
}
void update(int i,int n){
  for(;i<=n;i+=lowbit(i)){
    C[i] = A[i];
    for(int j=lowbit(i)>>1;j;j>>1) //枚举被管辖的数
      C[i] = max(C[i],C[i-j]);
  }
}
ll query(int l,int r){
  ll ans = 0;
  while(l<=r)
    if (r-lowbit(r)+1 >= l){ //保证C[r]代表的区间没有越界
      ans = max(ans,C[r]);
      r-=lowbit(r);
    }
    else{ // 否则只走一步
      ans = max(ans,A[r]);
      r--;
    }
  return ans;
}
void init(ll A[],int n){
  // memset(C,0,sizeof C);
  for(int i=1;i<=n;++i) update(i,n);
}


//区间更新，单点查询，只维护C,不会使用A。
ll C[N],c[N];
int lowbit(int x){ // 返回最低位的1
  return -x&x; 
}
void update(int i,int x,int n){ //只维护C和c,不会使用A。
  for(;i<=n;i+=lowbit(i))
    C[i]+=x;
}
ll query(int i){
  ll ans = 0;
  for(;i;i-=lowbit(i)) //每次处理一个长度为lowbit(i)的区间
    ans += C[i];
  return ans;
}
void updates(int l,int r,int x,int n){
  c[l] += x;
  update(l,x,n);
  c[r+1] -= x;
  update(r+1,-x,n);
}
void init(ll A[],int n){ //预处理，A下标从1开始
  // memset(C,0,sizeof C);
  c[1] = A[1];update(1,c[1],n);
  for(int i=2;i<=n;++i){
    c[i] = A[i] - A[i-1];
    update(i,c[i],n);
  }
}

//区间更新，区间查询, 只维护C,不会使用A。
ll C[N],C2[N],c[N],c2[N];
int lowbit(int x){ // 返回最低位的1
  return -x&x; 
}
void update(ll C[],int i,int x,int n){ //只维护C,不会使用其他数组。
  for(;i<=n;i+=lowbit(i))
    C[i]+=x;
}
ll query(ll C[],int i){
  ll ans = 0;
  for(;i;i-=lowbit(i)) //每次处理一个长度为lowbit(i)的区间
    ans += C[i];
  return ans;
}
void updates(int l,int r,int x,int n){
  c[l] += x;
  update(C,l,x,n);
  c[r+1] -= x;
  update(C,r+1,-x,n);
  c2[l] += (l-1)*x;
  update(C2,l,(l-1)*x,n);
  c2[r+1] -= r*x;
  update(C2,r+1,-r*x,n);
}
ll querys(int l,int r){
  return r*query(C,r) - query(C2,r) - ((l-1)*query(C,l-1) - query(C2,l-1) );
}
void init(ll A[],int n){ //A下标从1开始
  // memset(C,0,sizeof C); //如果只用一次这两句不用敲
  c[1] = A[1];update(C,1,c[1],n);
  c2[1] = 0;
  for(int i=2;i<=n;++i){
    c[i] = A[i] - A[i-1];
    update(C,i,c[i],n);
    c2[i] = (i-1)*c[i];
    update(C2,i,c2[i],n);
  }
}
