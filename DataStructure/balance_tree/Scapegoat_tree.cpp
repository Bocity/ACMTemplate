#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#define alpha 0.8
#define maxn 2000001
#define ri register
#define il inline
using namespace std;
struct scapegoat {
    int son[2], val, valid, total;  //valid (有效的子树点数)  total(总点数)
    bool exist;   //是否被删除  exist(1未删除0,已删除)
} e[maxn];
int memory[maxn];
int cur[maxn];
int root, pool, poi, cnt, to_rebuild;
il bool isbad(int now) { //判断要不要背锅2333
    if ((double) e[now].valid * alpha <= (double) max(e[e[now].son[0]].valid, e[e[now].son[1]].valid)) return true;
    return false;
}
void dfs(int &now) { //中序遍历暴躁拍扁Xander
    if (!now) return;
    dfs(e[now].son[0]);  //拍左脸
    if (e[now].exist)       //看看还活着吗
        cur[++poi] = now;   //活着扔到数组
    else
        memory[++pool] = now;    //挂了扔进棺材
    dfs(e[now].son[1]);    //拍右脸
}
void build(int l, int r, int &now) {
    int mid = (l + r) >> 1; 
    now = cur[mid];                 //取出中间元素
    if (l == r) {         //叶子
        e[now].son[0] = e[now].son[1] = 0;   
        e[now].total = e[now].valid = 1;
        return;
    }
    if (l < mid)
        build(l, mid - 1, e[now].son[0]);       //mid已经准备就绪
    else
        e[now].son[0] = 0;
    build(mid + 1, r, e[now].son[1]);
    e[now].total = e[e[now].son[0]].total + e[e[now].son[1]].total + 1;  //相当于maintain
    e[now].valid = e[e[now].son[0]].valid + e[e[now].son[1]].valid + 1;
}
il void rebuild(int &now) {   //暴躁老哥干死Xander
    poi = 0;
    dfs(now);
    if (poi)                     //poi为拍扁后数组大小
        build(1, poi, now);
    else                        //拍扁后真扁了。。
        now = 0;
}
il int find_rank(int k) {   
    int now = root;
    int ans = 1;
    while (now) {
        if (e[now].val >= k)   
            now = e[now].son[0];
        else {
            ans += e[e[now].son[0]].valid + e[now].exist;
            now = e[now].son[1];
        }
    }
    return ans;
}
il int find_kth(int k) {
    int now = root;
    while (now) {
        if (e[now].exist && e[e[now].son[0]].valid + 1 == k)
            return e[now].val;
        else if (e[e[now].son[0]].valid >= k)
            now = e[now].son[0];
        else {
            k -= e[e[now].son[0]].valid + e[now].exist;
            now = e[now].son[1];
        }
    }
}
void insert(int &now, int val) {
    if (!now) {    //找到叶子
        now = memory[pool--];      //对棺材里的结点使用滑稽币复活
        e[now].val = val;   
        e[now].exist = e[now].total = e[now].valid = 1;  //颁发良民证
        e[now].son[0] = e[now].son[1] = 0;
        return;
    }
    e[now].total++, e[now].valid++;  //告诉路上的老哥，新来了一个小弟
    if (e[now].val >= val)          //扔到该去的地方
        insert(e[now].son[0], val);
    else
        insert(e[now].son[1], val);
    if (!isbad(now)) {              
        if (to_rebuild) {           //儿子被暴躁
            if (e[now].son[0] == to_rebuild)
                rebuild(e[now].son[0]);     //左儿子被暴躁
            else
                rebuild(e[now].son[1]);     //右儿子被暴躁
            to_rebuild = 0;
        }
    } else        //放不下了突然暴躁
        to_rebuild = now;
}
il void delete_pos(int &now, int tar) // target(目标) 删除排名为tar的数
{
    if (e[now].exist && e[e[now].son[0]].valid + 1 == tar) {   
        e[now].exist = 0;
        e[now].valid--;     
        return;
    }
    e[now].valid--;   //回收良民证
    if (e[e[now].son[0]].valid + e[now].exist >= tar)
        delete_pos(e[now].son[0], tar);
    else
        delete_pos(e[now].son[1], tar - e[e[now].son[0]].valid - e[now].exist);
}
il void delete_val(int tar) {    //删除值为tar的数
    delete_pos(root, find_rank(tar));
    if ((double) e[root].total * alpha > e[root].valid) rebuild(root);
}
int main() {
    int opt, x, m;
    for (int i = 2000000; i >= 1; i--) memory[++pool] = i;
    scanf("%d", &m);
    while (m--) {
        scanf("%d%d", &opt, &x);
        if (opt == 1) {
            insert(root, x);
        }
        if (opt == 2) {
            delete_val(x);
        }
        if (opt == 3) {
            printf("%d\n", find_rank(x));
        }
        if (opt == 4) {
            printf("%d\n", find_kth(x));
        }
        if (opt == 5) {
            printf("%d\n", find_kth(find_rank(x) - 1));
        }
        if (opt == 6) {
            printf("%d\n", find_kth(find_rank(x + 1)));
        }
    }
    return 0;
}