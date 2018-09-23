#include <bits/stdc++.h>
using namespace std;
#define maxn 100005
int pre[maxn], ch[maxn][2], key[maxn], rt, tot;
void newNode(int& r, int fa, int val){
    r = ++tot;
    pre[r] = fa;
    key[r] = val;
    ch[r][0] = ch[r][1] = 0;
}
void rotate(int r, int kind){
    int y = pre[r];
    ch[y][!kind] = ch[r][kind];
    pre[ch[r][kind]] = y;
    if(pre[y]){
        ch[pre[y]][ch[pre[y]][1] == y] = r;
    }
    ch[r][kind] = y;
    pre[r] = pre[y];
    pre[y] = r;
}
void splay(int r, int goal){
    while(pre[r] != goal){
        if(pre[pre[r]] == goal){
            rotate(r, ch[pre[r]][0] == r);
        }
        else{
            int y = pre[r];
            int kind = ch[pre[y]][0] == y;
            if(ch[pre[r]][!kind] == r){
                rotate(y, kind);
                rotate(r, kind);
            }
            else{
                rotate(r, !kind);
                rotate(r, kind);
            }
        }
    }
    if(goal == 0) rt = r;
}
int insert(int val){
    int r = rt;
    while(1){
        if(val < key[r]){
            if(ch[r][0]) r = ch[r][0];
            else break;
        }
        else if(val > key[r]){
            if(ch[r][1]) r = ch[r][1];
            else break;
        }
        else return 0;
    }
    newNode(ch[r][val > key[r]], r, val);
    splay(ch[r][val > key[r]], 0);
    return 1;
}
int getmin(int val){
    int r = rt;
    if(ch[r][0] == 0) return 1 << 29;
    r = ch[r][0];
    while(ch[r][1]) r = ch[r][1];
    return key[r];
}
int getmax(int val){
    int r = rt;
    r = ch[r][1];
    if(r == 0) return 1 << 29;
    while(ch[r][0]) r = ch[r][0];
    return key[r];
}
int main(){
    int n, x;
    scanf("%d", &n);
    int ans = 0;
    rt = tot = 0;
    for(int i = 1; i <= n; ++i){
        scanf("%d", &x);
        if(rt == 0){
            newNode(rt, 0, x);
            ans += x;
        }
        else{
            if(insert(x) == 0){
                continue;
            }
            else{
                int l = getmin(x);
                int r = getmax(x);
                ans += min(abs(l - x), abs(r - x));
            }
        }
    }
    printf("%d\n", ans);
}
 
/*
题意：4e4天，每天有一个营业额，找到当天之前营业额与当天营业额差值最小的一天，然后累加这个差值。
思路：
这题可以用set来维护前缀，然后用lowerbound和upperbound来找。作为splay的模板题也是不错的。
注意第一天差值就是第一天的营业额。后面如果插入的值已经存在，就不能重复插入，然后找前驱和后继，
简单的在splay上dfs即可。
*/
