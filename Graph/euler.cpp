//match 顶点度
//Directed graph
void solve(int x) {
  int i;
  if (!match[x]) {
    path[++l]=x;
    return ;
  }
  for (i=1; i<=n; i++)
    if (b[x][i]) {
      b[x][i]--;
      match[x]--;
      solve(i);
    }
  path[++l]=x;
}
//Undirected graph
void solve(int x) {
  int i;
  if (!match[x]) {
    path[++l]=x;
    return ;
  }
  for (i=1; i<=n; i++)
    if (b[x][i]) {
      b[x][i]--;
      b[i][x]--;
      match[x]--;
      match[i]--;
      solve(i);
    }
  path[++l]=x;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
//C++
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <stack>
#include <string>
#include <list>
#include <queue>
#include <map>
#include <vector>
#include <deque>
#include <set>
using namespace std;

//*************************OUTPUT*************************
#ifdef WIN32
#define INT64 "%I64d"
#define UINT64 "%I64u"
#else
#define INT64 "%lld"
#define UINT64 "%llu"
#endif

//**************************CONSTANT***********************
#define INF 0x3f3f3f3f
#define eps 1e-8
#define PI acos(-1.)
#define PI2 asin (1.);
typedef long long LL;
//typedef __int64 LL;   //codeforces
typedef unsigned int ui;
typedef unsigned long long ui64;
#define MP make_pair
typedef vector<int> VI;
typedef pair<int, int> PII;
#define pb push_back
#define mp make_pair

//***************************SENTENCE************************
#define CL(a,b) memset (a, b, sizeof (a))
#define sqr(a,b) sqrt ((double)(a)*(a) + (double)(b)*(b))
#define sqr3(a,b,c) sqrt((double)(a)*(a) + (double)(b)*(b) + (double)(c)*(c))

//****************************FUNCTION************************
template <typename T> double DIS(T va, T vb) { return sqr(va.x - vb.x, va.y - vb.y); }
template <class T> inline T INTEGER_LEN(T v) { int len = 1; while (v /= 10) ++len; return len; }
template <typename T> inline T square(T va, T vb) { return va * va + vb * vb; }

// aply for the memory of the stack
//#pragma comment (linker, "/STACK:1024000000,1024000000")
//end

const int maxn = 2000+10;
struct stack{
    int top;
    int node[maxn];
}s;
int edges[maxn][maxn];//顶点的栈结构
int n,m;//顶点个数,边数


void dfs(int x){
    s.top++;
    s.node[s.top]=x;//x入栈
    for(int i=0;i<n;i++){
        if(edges[i][x]>0){//存在边
            edges[i][x]=0  ; edges[x][i]=0;//删除此边
            dfs(i);//继续深搜
            break;
        }
    }
}

void fleury(int x){//fleury算法
    int b;
    s.top=0;  s.node[s.top]=x;//入栈
    while(s.top>=0){//栈不空
        b=0;//判断点是否可以继续扩展
        for(int i=0;i<n;i++){
            if(edges[s.node[s.top]][i]>0){//存在边就是可以扩展
                b=1;
                break;
            }
        }
        if(b==0) {//如果没有点可以扩展，输出并出栈
            printf("%d ",s.node[s.top]+1);//因为输入的时候自己处理时顶点--了，所以这里+1
            s.top--;//栈顶指针往下移动一格
        }
        else {
            s.top--;//关键不可少
            //printf("s.top=%d\n",s.top);
            //printf("s.node[s.top+1]=%d\n",s.node[s.top+1]);
            dfs(s.node[s.top+1]);//如果有就dfs,继续扩展
        }
    }
}

int main(){
    int s,t;//读入边的起点和终点
    int degree,num,start;//每个顶点的度，奇度顶点的个数，欧拉回路的起点
    while(scanf("%d%d",&n,&m)!=EOF){//顶点个数，边数
        memset(edges,0,sizeof(edges));
        for(int i=0;i<m;i++){
            scanf("%d%d",&s,&t);
            edges[s-1][t-1]=edges[t-1][s-1]=1;
        }
        //如果存在奇度顶点，则从奇度顶点出发，否则从顶点0出发
        num=0; start=0;//奇度顶点的个数,欧拉回路的起点
        for(int i=0;i<n;i++){//计算每个顶点的度数（出度+入度）
            degree=0;
            for(int j=0;j<n;j++){
                degree+=edges[i][j];
            }
            if(degree%2==1){
                start=i;  num++;
            }
        }
        if(num==0||num==2) {fleury(start);}
        else {
            printf("NO Eular path\n");
        }
    }
    return 0;
}


