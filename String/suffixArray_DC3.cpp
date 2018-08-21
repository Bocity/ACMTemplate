#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>
#define ccnb 0

#define F(x) ((x) / 3 + ((x) % 3 == 1 ? 0 : tb))
#define G(x) ((x) < tb ? (x)*3 + 1 : ((x)-tb) * 3 + 2)
using namespace std;
const int N = 2e5 + 10;
const int inf = 0x3f3f3f3f;
struct SuffixArray
{
    int r[N * 3];
    int sa[N * 3], rk[N], height[N];
    int wa[N], wb[N], wv[N], ws[N];
    int m, n;
    void init(int *s, int len)
    {
        memset(r, 0, sizeof(r));
        memset(sa, 0, sizeof(sa));
        n = len;
        for (int i = 0; i < n; i++)
        {
            r[i] = int(s[i]);
        }
        m = 500;
    }
    int c0(int *r, int a, int b)
    {
        return r[a] == r[b] && r[a + 1] == r[b + 1] && r[a + 2] == r[b + 2];
    }
    int c12(int k, int *r, int a, int b)
    {
        if (k == 2)
            return r[a] < r[b] || r[a] == r[b] && c12(1, r, a + 1, b + 1);
        else
            return r[a] < r[b] || r[a] == r[b] && wv[a + 1] < wv[b + 1];
    }
    void my_sort(int *r, int *a, int *b, int n, int m)
    {
        int i;
        for (i = 0; i < n; i++)
            wv[i] = r[a[i]];
        for (i = 0; i < m; i++)
            ws[i] = 0;
        for (i = 0; i < n; i++)
            ws[wv[i]]++;
        for (i = 1; i < m; i++)
            ws[i] += ws[i - 1];
        for (i = n - 1; i >= 0; i--)
            b[--ws[wv[i]]] = a[i];
        return;
    }
    void buildSA(int *r, int *sa, int n, int m)
    { // DC3
        int i, j, *rn = r + n, *san = sa + n, ta = 0, tb = (n + 1) / 3, tbc = 0, p;
        r[n] = r[n + 1] = 0;
        for (i = 0; i < n; i++)
            if (i % 3 != 0)
                wa[tbc++] = i;
        my_sort(r + 2, wa, wb, tbc, m);
        my_sort(r + 1, wb, wa, tbc, m);
        my_sort(r, wa, wb, tbc, m);
        for (p = 1, rn[F(wb[0])] = 0, i = 1; i < tbc; i++)
        {
            rn[F(wb[i])] = c0(r, wb[i - 1], wb[i]) ? p - 1 : p++;
        }
        if (p < tbc)
            buildSA(rn, san, tbc, p);
        else
            for (i = 0; i < tbc; i++)
                san[rn[i]] = i;
        for (i = 0; i < tbc; i++)
            if (san[i] < tb)
                wb[ta++] = san[i] * 3;
        if (n % 3 == 1)
            wb[ta++] = n - 1;
        my_sort(r, wb, wa, ta, m);
        for (i = 0; i < tbc; i++)
            wv[wb[i] = G(san[i])] = i;
        for (i = 0, j = 0, p = 0; i < ta && j < tbc; p++)
        {
            sa[p] = c12(wb[j] % 3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
        }
        for (; i < ta; p++)
            sa[p] = wa[i++];
        for (; j < tbc; p++)
            sa[p] = wb[j++];
        return;
    }

    void getHeight()
    {
        int i, j, k = 0;
        for (i = 1; i <= n; i++)
            rk[sa[i]] = i;
        for (i = 0; i < n; height[rk[i++]] = k)
            for (k ? k-- : 0, j = sa[rk[i] - 1]; r[i + k] == r[j + k]; k++)
                ;
        return;
    }
    void call(int *s, int len)
    {
        init(s, len);
        buildSA(r, sa, n + 1, m);
        getHeight();
    }
    int d[N][20];
    void initRMQ(int *A, int n)
    {
        for (int i = 1; i <= n; i++)
            d[i][0] = A[i];
        for (int j = 1; (1 << j) <= n; j++)
        {
            for (int i = 1; i + j - 1 <= n; i++)
            {
                d[i][j] = min(d[i][j - 1], d[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    int RMQ(int L, int R)
    {
        int k = 0;
        while ((1 << (k + 1)) <= R - L + 1)
            k++;
        return min(d[L][k], d[R - (1 << k) + 1][k]);
    }
    void initLCP()
    {
        initRMQ(height, n);
    }
    int LCP(int i, int j)
    {
        if (rk[i] > rk[j])
            swap(i, j);
        return RMQ(rk[i] + 1, rk[j]);
    }
} solver;