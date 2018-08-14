// 所有下标从1开始

int lowbit(int x){ // 返回最低位的1
  return -x&x; // 原理：-x是取x的补码，即反码+1。二进制数加一时最低位的0成为1，更低的1都成为0。因此-x&x，最低位的1（反码中最低位的0）会保留下来，其他都会变成0，这样就得到了x的最低位的1
}

ll A[N];
//树状数组维护前缀和。只维护C,不会使用A。
//但凡具有区间和性质的函数都可以用树状数组维护前缀和
//但凡有区间差性质的函数都可以用前缀和维护区间和，比如乘，加，注意初始值不同
//如果按值插入则可以做到维护在当前元素左边/右边的比它大/小的数的函数和
ll C[N];
void update(int i,ll x,int n){ //需要手动初始化
  for(;i<=n;i+=i&(-i)) C[i]+=x;
}
ll query(int i){
  ll ans = 0;
  for(;i;i-=i&(-i)) //每次处理一个长度为lowbit(i)的区间
    ans += C[i];
  return ans;
}

//树状数组维护区间最值，A[i]必须已经更新
//但凡具有区间并性质的函数都可以用此方式维护，比如gcd
ll C[N];
void update(int i,int n){
  for(;i<=n;i+=i&(-i)){
    C[i] = A[i];
    for(int j=i&(-i>)>1;j;j>>1) //枚举被管辖的数
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


//区间更新，单点查询，只维护C,不会使用A。
//C维护的不是A，而是差分数组c的前缀和
ll C[N];
void update(int i,ll x,int n){ //只维护C和c,不会使用A。
  for(;i<=n;i+=i&(-i))
    C[i]+=x;
}
void updates(int l,int r,ll x,int n){
  update(l,x,n);
  update(r+1,-x,n);
}
ll query(int i){
  ll ans = 0;
  for(;i;i-=i&(-i)) //每次处理一个长度为lowbit(i)的区间
    ans += C[i];
  return ans;
}
void init(ll A[],int n){ //预处理，A下标从1开始
  // memset(C,0,sizeof C);
  for(int i=1;i<=n;++i)
    update(i,A[i] - A[i-1],n);
}

//区间更新，前缀查询, 只维护C,不会使用A。
//C维护的是差分数组c，C2维护的是c2[i] = (i-1)*c[i]
ll C[N],C2[N];
void update(int r,ll x,int n){ //只维护C,不会使用其他数组。
  for(int i=;i<=n;i+=i&(-i)){
    C[i] += x;
    C2[i] += (r-1)*x;
  }
}
void updates(int l,int r,ll x,int n){
  update(l,x,n);
  update(r+1,-x,n);
}
ll query(int r){
  ll ans = 0;
  for(int i=r;i;i-=i&(-i)) //每次处理一个长度为lowbit(i)的区间
    ans += r*C[i]-C2[i];
  return ans;
}
void init(ll A[],int n){ //A下标从1开始
  // memset(C,0,sizeof C); //如果只用一次这两句不用敲
  for(int i=1;i<=n;++i)
    update(i,A[i]-A[i-1],n);
}

//权值树状数组操作
//查排名
ll C[N];
int myrank(int i) {
  int res = 1;
	for (--i; i; i -= i & -i) res += C[i];
  return res;
}
void update(int i,ll x,int n){ //需要手动初始化
  for(;i<=n;i+=i&(-i)) C[i]+=x;
}
// 查区间kth 小 
int findk(int k,int n) {
    int ans = 0, cnt = 0;
    for (int i = 30; i >= 0; --i) {
        ans += (1 << i);
        if (ans > n || cnt + C[ans] >= k)
            ans -= (1 << i);
        else
            cnt += C[ans];
    }
    return (ans + 1);
}
//查x的前驱
findk(myrank(x)-1,n);
//查x的后继
findk(myrank(x + 1),n);


//二维树状数组，区间更新