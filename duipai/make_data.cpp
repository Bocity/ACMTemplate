#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
#define mp make_pair

ll random(ll l,ll r){ // [l,r)
  return (ll)rand()%(r-l)+l;
}

void make_tree(){
  int n = random(10,20);
  cout<<n<<endl;
  for(int i=2;i<=n;i++){
    int fa =  random(1,i);
    cout<<fa<<" ";
  }cout<<endl;
  // i连1..i-1的点
}

// 简单连通无向图
pii e[1000000];
map<pii,int> h;
void make_graph(){
  int n = random(10,20);
  int m = random(2*n,n*(n-1)/2+1);
  cout<<n<<" "<<m<<endl;

  // 生成树，保证连通
  for(int i=2;i<=n;i++){
    int fa = random(1,i);
    e[i-1] = mp(fa,i);
    h[e[i-1]] = h[mp(i,fa)] = 1;
  }

  // 生成剩下m-n+1条边
  for (int i=n;i<=m;++i){
    int x,y;
    do{
      x = random(1,n+1),y = random(1,n+1);
    }while(x == y || h.count({x,y}));
    e[i] = mp(x,y);
    h[e[i]] = h[mp(y,x)] = 1;
  }

  random_shuffle(e+1,e+m+1);
  for(int i=1;i<=m;++i) 
    cout<<e[i].first<<" "<<e[i].second<<endl;
}

// 菊花图
// 链图
// 蒲公英图

int main(){
  std::ios::sync_with_stdio(false);
  srand((unsigned)time(NULL));

  // make_tree();
  make_graph();
}