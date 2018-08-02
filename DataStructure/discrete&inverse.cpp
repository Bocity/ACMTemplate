// tmp为原数组的拷贝，d为原数组
// n为数组长度，下标从1开始。如果从0开始，把所有的tmp+1改成tmp。值不变，依然是1..m。
// 排序之后去重，然后每个元素的值为在排序后的数组中到起始的距离+1
// 离散化之后值为1..m（去重后的个数）
//O(n log n)
//下标从1开始

ll C[N];
void update(int i,int x,int n){ //需要手动初始化
  for(;i<=n;i+=i&(-i)) C[i]+=x;
}
ll query(int i){
  ll ans = 0;
  for(;i;i-=i&(-i)) //每次处理一个长度为lowbit(i)的区间
    ans += C[i];
  return ans;
}

int tmp[N];
int d[N];
int n;
void discrete(){
  sort(tmp+1,tmp+1+n);
  int m=unique(tmp+1,tmp+1+m)- (tmp+1);
  for (i=1;i<=n;++i) d[i]=lower_bound(tmp+1,tmp+1+m,d[i])-(tmp+1) + 1;
}

int main(){
  discrete();

  //求每个元素后面的比它小的值，查询d[i]-1，插入d[i]
  //如果是小于等于，查询d[i]
  //如果包括当前元素，先插入再查询
  //求每个元素后面的比它大的值，需要插入相反的值，d[i]映射后为n-d[i]+1
  //求每个元素前面的值，则正着循环
  ll ans=0;
  for(i=n;i>=1;--i) { 
    ans += query(d[i]-1);
    update(d[i],1,n);
  }
}
