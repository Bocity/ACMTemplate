#include<bits/stdc++.h>
using namespace std;
#define mem(a,x) memset(a,x,sizeof a)

int main(){
  auto print = [](auto x){cout<<x<<" ";};
  // 单字节，任意赋值
  char ch[100];
  mem(ch,'q');
  for_each(ch,ch+20,print);cout<<endl;

  bool flag[100];
  mem(flag,1);
  for_each(flag,flag+20,print);cout<<endl;

  // 整型，0xff = -1, 0x3f是最值的一半（常用INF），0x7f接近最值但是运算可能溢出
  // 常用赋值：0,-1,0x3f
  int ans[100];
  mem(ans,0x3f);
  for_each(ans,ans+20,print);cout<<endl;

  long long ans2[100];
  mem(ans2,0x3f);
  for_each(ans2,ans2+20,print);cout<<endl;
  cout<<LLONG_MAX<<endl;
}