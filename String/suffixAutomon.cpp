#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int inf = 0x3f3f3f3f;

struct SAM
{
    int last, tot, n, root;
    int ch[N << 1][26], link[N << 1], maxlen[N << 1];
    int num[N], id[N << 1];

    int mat[N << 1], f[N << 1];

    void init()
    {
        tot = 0;
        last = root = newnode();
    }
    int newnode()
    {
        ++tot;
        memset(ch[tot], 0, sizeof ch[tot]);
        maxlen[tot] = link[tot] = 0;
        return tot;
    }
    void add(int c)
    {
        int now = newnode();
        maxlen[now] = maxlen[last] + 1;

        while (last && ch[last][c] == 0)
        {
            ch[last][c] = now, last = link[last];
        }
        if (last)
        {
            int x = ch[last][c];
            if (maxlen[x] == maxlen[last] + 1)
            {
                link[now] = x;
            }
            else
            {
                int nq = newnode();
                maxlen[nq] = maxlen[last] + 1;
                memcpy(ch[nq], ch[x], sizeof ch[x]);
                link[nq] = link[x];
                link[x] = link[now] = nq;
                while (last && ch[last][c] == x)
                {
                    ch[last][c] = nq;
                    last = link[last];
                }
            }
        }
        else
            link[now] = 1;
        last = now;
    }
    void build(char *s)
    {
        init();
        int len = strlen(s);
        for (int i = 0; i < len; ++i)
        {
            add(s[i] - 'a');
        }
        n = len;
    }
    void build(int *s, int l)
    {
        init();
        for (int i = 0; i < l; ++i)
        {
            add(s[i]);
        }
        n = l;
    }
    void topo()
    {
        for (int i = 1; i <= tot; ++i)
            num[maxlen[i]]++;
        for (int i = 1; i <= n; ++i)
            num[i] += num[i - 1];
        for (int i = 1; i <= tot; ++i)
            id[--num[maxlen[i]]] = i;
        fill_n(mat + 1, tot, inf);
    }
    void query(char *s)
    {
        int l = strlen(s);
        int ans = 0, len = 0;
        fill_n(f + 1, tot, 0);
        for (int p = root, i = 0; i < l; i++)
        {
            while (p > 1 && !ch[p][s[i] - 'a'])
                p = link[p], len = maxlen[p];
            if (ch[p][s[i] - 'a'])
            {
                p = ch[p][s[i] - 'a'];
                f[p] = max(f[p], ++len);
            }
        }
        for (int i = tot; i >= 1; --i)
        {
            if (f[id[i]])
            {
                f[link[id[i]]] = maxlen[link[id[i]]];
            }
        }
        for (int i = 1; i <= tot; ++i)
        {
            mat[i] = min(mat[i], f[i]);
        }
    }
    int res()
    {
        int ans = 0;
        for (int i = 1; i <= tot; ++i)
            ans = max(ans, mat[i]);
        return ans;
    }
} sam;
