// Xander的莫队。在modui内读入询问，输出答案
// 需要更改移动操作。注意区间的下标和原数组的下标。
struct Query{
  int l,r,id,num;
  bool operator < (Query& b){
    if (num!=b.num) return num<b.num;
    else return r<b.r;
  /*奇偶优化 blocks == 500优化
    if (pos[a.l]%2) return a.r < b.r;
    return a.r > b.r;
    */
  }
}Q[N];//id为询问序号，num为块序号
ll ans[N];
void modui(int n,int q){ // 答案存在ans里
  int block = (int)(sqrt(n)+0.5);//块大小
  
  int li,ri;
  llp(i,0,q){  //读入查询
    scanf("%d%d",&li,&ri);
    Q[i] = Query{li,ri,i,li/block};
  }
  
  sort(Q,Q+q); 
  // llp(i,0,q) printf("Q = %d l = %d r = %d num = %d\n",Q[i].id,Q[i].l,Q[i].r,Q[i].num);
  
  int l = 0,r = 0;
  ll tmp = 1;
  llp(i,0,q){ // 移动，需要更改
    while(r<Q[i].r)  {tmp = subp(addp(tmp,tmp),C(r,l)); r++;} //r右移
    while(r>Q[i].r)  {tmp = addp(tmp,C(r-1,l))*inv[2]%MOD; r--;} //r左移
    while(l<Q[i].l)  {tmp = addp(tmp, C(r,l+1)); l++;} //l右移
    while(l>Q[i].l)  {tmp = subp(tmp, C(r,l)); l--;} //l左移
    ans[Q[i].id] = tmp;
  }

  llp(i,0,q) printf("%lld\n",ans[i]);
}

// ------------------------------------------------------------------------

// Bocity的莫队

#include <bits/stdc++.h>
// 注意每次flag l r 的初始化 以及有可能会爆longlong
// 莫队算法时间复杂度 O（N^1.5）
using namespace std;
const long long maxn =100000+10;
typedef long long ll;
struct node{
    int l,r,id;
}Q[maxn];
int n,m,k;
int L=1,R=0;
long long Ans=0;
int pos[maxn];
long long ans[maxn];
int flag[maxn];
int a[maxn];
bool cmp (node a,node b){
    if (pos[a.l]==pos[b.l])
    return a.r<b.r;
	/*奇偶优化 blocks == 500优化
	  if (pos[a.l]%2) return a.r < b.r;
	  return a.r > b.r;
	   */
    return pos[a.l]<pos[b.l];
}
inline void add(int x){
    flag[a[x]]=1;
    if (flag[a[x]-1]==1&&flag[a[x]+1]==1){
        Ans--;
    }
    if (flag[a[x]-1]==0&&flag[a[x]+1]==0){
        Ans++;
    }
}
inline void del (int x){
    flag[a[x]]=0;
    if (flag[a[x]-1]==1&&flag[a[x]+1]==1){
        Ans++;
    }
    if (flag[a[x]-1]==0&&flag[a[x]+1]==0){
        Ans--;
    }
}

int main(){
    ios::sync_with_stdio(false);
    int T;
    cin>>T;
   while (T--){
    Ans=0;
    cin>>n>>m;
    int sz=sqrt(n);
        for(int i=1;i<=n;++i){
            cin>>a[i];
            pos[i]=i/sz;
        }
        for(int  i=1;i<=m;++i){
            cin>>Q[i].l>>Q[i].r;
            Q[i].id=i;
        }
        sort(Q+1,Q+1+m,cmp);
        L=1,R=0;
        memset(flag,0,sizeof flag);
        for(int i=1;i<=m;++i){
           while(R>Q[i].r){
                del(R);
                R--;
            }
            while(R<Q[i].r){
                R++;
                add(R);
            }
            while(L<Q[i].l){
                del(L);
                L++;
            }
            while(L>Q[i].l){
                L--;
                add(L);
            }
                ans[Q[i].id]=Ans;
        }

        for(int  i=1;i<=m;++i){
                cout<<ans[i]<<"\n";
         }
   }
    return 0;
}

