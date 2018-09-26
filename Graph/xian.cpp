// 连接环上两个不相邻节点的边称为弦。
// 弦图的定义：若一张无向图中任意一个大小超过3的环都存在至少一条弦，那么这样的图称为弦图。
// 单纯点：与其相邻的点集的诱导子图（把所以的边都连上后生成的图）是一个团（任两个点之间都有边）。
// 完美消除序列：一个点的排列v1,v2...vn满足vi在vi,vi+1...vn的诱导子图中为一个单纯点。
// 定理：一个无向图是弦图当且仅当它有一个完美消除序列。
// 用最大势算法(Maximum Cardinality Search)可以在O(n+m)内求出一个消除序列的反序。
// 只要倒过来就可以了。
// for (int i=n,now;i;--i)
// {
//     bool fg=0;
//     while (!fg)
//     {
//         for (int j=v[best].size()-1;j>=0;--j)
//             if (!vis[v[best][j]]) {fg=1;now=v[best][j];break;}
//             else v[best].pop_back();
//         if (!fg) --best;
//     }
//     seq[i]=now;rk[now]=i;vis[now]=1;
//     for (int e=head[now];e;e=nxt[e])
//         if (!vis[to[e]])
//         {
//             v[++label[to[e]]].push_back(to[e]);
//             best=max(best,label[to[e]]);
//         }
// }
/*
 *  弦图判断
 *  INIT: g[][]置为邻接矩阵;
 *  CALL: mcs(n); peo(n);
 *  第一步: 给节点编号 mcs(n)
 *  设已编号的节点集合为A, 未编号的节点集合为B
 *  开始时A为空, B包含所有节点.
 *  for num=n-1 downto 0 do {
 *      在B中找节点x, 使与x相邻的在A集合中的节点数最多,
 *      将x编号为num，并从B移入A。
 *  }
 *  第二部：检查peo(n)
 *  for num=0 to n-1 do {
 *      对编号为num的点x，设所有编号>num且与x相邻的点集为C
 *      在C中找出编号最小的节点y，
 *      若C中存在x != y，使得y与x之间无边，则此图不是弦图。
 *  }
 *  检查完毕, 则此图是弦图.
 */
//  最小色数问题
// 等于最小团数，也就是maxni=1label[i]+1
// 最大独立集等于最小团覆盖数。按照完美消除序列一个个贪心选取即可。
//n^2
const int V = 10010;
int g[V][V], order[V], inv[V], tag[V];

void mcs(int n)
{
    int i, j, k;
    memset(tag, 0, sizeof(tag));
    memset(order, -1, sizeof(order));
    for (i = n - 1; i >= 0; i--)
    {   //  vertex:0~n-1
        for (j = 0; order[j] >= 0; j++);
        for (k = j + 1; k < n; k++)
        {
            if (order[k] < 0 && tag[k] > tag[j])
            {
                j = k;
            }
        }
        order[j] = i, inv[i] = j;
        for (k = 0; k < n; k++)
        {
            if (g[j][k])
            {
                tag[k]++;
            }
        }
    }
    return ;
}

int peo(int n)
{
    int i, j, k, w, min;
    for (i = n - 2; i >= 0; i--)
    {
        j = inv[i], w = -1, min = n;
        for (k = 0; k < n; k++)
        {
            if (g[j][k] && order[k] > order[j] && order[k] < min)
            {
                min = order[k], w=k;
            }
        }
        if (w < 0)
        {
            continue;
        }
        for (k = 0; k < n; k++)
        {
            if (g[j][k] && order[k] > order[w] && !g[k][w])
            {
                return 0;   //  no
            }
        }
    }
    return 1;               //  yes
}

