#include<queue>
#include<cstdio>
using namespace std;


// priority_queue<Type, Container, Functional>
// 内部用堆实现，插入删除复杂度logn

//1.默认大根堆
priority_queue<int> Q;

//2.升序
priority_queue<int,vector<int>,greater<int> > Q2;

//3.自定义: 定义cmp结构体重载()，或者在元素内定义<号
struct node{
  int x,y,z;
};
struct cmp{ 
  bool operator()(node& a,node& b){// <升序，>降序（为真则b上升）
    if (a.x==b.x)
      if (a.y==b.y) return a.z<b.z;
      else return a.y<b.y;
    else return a.x<b.x;
  }
};
priority_queue<node,vector<node>,cmp > Q3;

int main(){
  for(int i=0;i<10;++i){
    Q3.push(node{i,i,i});
  }
  while(!Q3.empty()){
    printf("%d %d %d\n",Q3.top().x,Q3.top().y,Q3.top().z);
    Q3.pop();
  }
}