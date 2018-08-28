//  洛谷 P4512 【模板】多项式除法

#include<bits/stdc++.h>
using namespace std;
const int mod=998244353,g=3;
const int N=3e5+1000;
int n,m,rvg,a[N],b[N],c[N],d[N],rv[N],ans[N];

inline int ad(int x,int y) {x+=y;if(x>=mod) x-=mod;return x;}
inline int dc(int x,int y) {x-=y;if(x<0) x+=mod;return x;}
inline int mul(int x,int y) {return 1ll*x*y%mod;}

template<class T>
inline void rd(T &x)
{
    char c=getchar();int f=0;x=0;
    while(!isdigit(c)) {if(c=='-') f=1;c=getchar();}
    while(isdigit(c)) {x=x*10+(c^48);c=getchar();}
    if(f) x=-x;
}

inline int fp(int x,int y)
{
    int re=1;
    for(;y;y>>=1,x=mul(x,x))
     if(y&1) re=mul(re,x);
    return re;
}

inline void NTT(int *e,int ptr,int n)
{
    int i,j,k,ori,pd,ix,iy,G;G= ptr?g:rvg;
    for(i=0;i<n;++i) if(i<rv[i]) swap(e[i],e[rv[i]]);
    for(i=1;i<n;i<<=1){
        ori=fp(G,(mod-1)/(i<<1));
        for(j=0;j<n;j+=(i<<1)){
            pd=1;
            for(k=0;k<i;++k,pd=mul(pd,ori)){
                ix=e[j+k];iy=mul(e[i+j+k],pd);
                e[j+k]=ad(ix,iy);e[i+j+k]=dc(ix,iy);
            }
        }
    }
    if(ptr) return;
    G=fp(n,mod-2);
    for(i=0;i<n;++i) e[i]=mul(e[i],G);
}

inline void getinv(int n,int *a,int *b)
{
    if(n==1) {b[0]=fp(a[0],mod-2);return;}
    getinv((n+1)>>1,a,b);
    int i,j,L=0,len=1;
    for(;len<n+n;len<<=1) L++;
    for(i=1;i<len;++i) rv[i]=((rv[i>>1]>>1)|((i&1)<<(L-1)));
    for(i=0;i<n;++i) d[i]=a[i];
    for(i=n;i<len;++i) d[i]=0;
    NTT(b,1,len);NTT(d,1,len);
    for(i=0;i<len;++i) b[i]=mul(b[i],dc(2,mul(b[i],d[i])));
    NTT(b,0,len);
    for(i=n;i<len;++i) b[i]=0;
}

inline void getmul(int *a,int *b,int *c,int n,int m)
{
    int i,j,len=1,L=0;
    for(;len<n+m;len<<=1) L++;
    for(i=1;i<len;++i) rv[i]=((rv[i>>1]>>1)|((i&1)<<(L-1)));
    static int u[N],k[N];
    for(i=0;i<n;++i) u[i]=a[i];for(i=n;i<len;++i) u[i]=0;
    for(i=0;i<m;++i) k[i]=b[i];for(i=m;i<len;++i) k[i]=0;
    NTT(u,1,len);NTT(k,1,len);
    for(i=0;i<len;++i) c[i]=mul(u[i],k[i]);
    NTT(c,0,len);
}

int main(){
    int i,j;
    rd(n);rd(m);rvg=fp(g,mod-2);
    for(i=n;i>=0;--i) rd(a[i]);
    for(i=m;i>=0;--i) rd(b[i]);
    n++;m++;
    getinv(n-m+1,b,c);
    getmul(a,c,d,n,n-m+1);

    reverse(d,d+n-m+1);
    for(i=0;i<=n-m;++i) ans[i]=d[i],printf("%d ",ans[i]);
    reverse(a,a+n);reverse(b,b+m);
    puts(""); 
    getmul(b,ans,c,m,n-m+1);
    for(i=0;i<m-1;++i) printf("%d ",dc(a[i],c[i]));
}