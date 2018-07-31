#include<bits/stdc++.h>
using namespace std;

#define llp(i,x,y) for(int i=x;i<y;++i) // [x,y) x->y
typedef long long ll;

const ll N=2e5+50;
struct node{
  ll x,y;
  int ind;
}P[N];
ll cross(node a,node b,node c){ // CA X CB
  node ca = node{a.x - c.x,a.y-c.y,0};
  node cb = node{b.x - c.x,b.y-c.y,0};
  return ca.x*cb.y - cb.x*ca.y;
} 
bool cmp(node& a,node& b){// 水平排序，左下角有点情况
  if (a.x != b.x) return a.x<b.x;
  if (a.y != b.y) return a.y>b.y;
  return a.ind < b.ind;
}
int Q[N];

void convex(int n){
    sort(P+1,P+n+1,cmp);
    
    // Graham
    int top=0;
    Q[top++] = 1;
    llp(i,2,n+1){
      while (top>=2 && cross(P[Q[top-1]],P[Q[top-2]],P[i])<0 )
         top--;
      Q[top++] = i;
    }

}
