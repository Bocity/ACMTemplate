#include <bits/stdc++.h>
#define endl "\n"
using namespace std;
typedef long long ll;
typedef vector<int> vci;
const ll MOD = 1e9 + 7;
const int N = 1e6 + 10;

char s[N * 2];

struct H
{
    ll hash;
    ll hash2;
    int k;
} _hash[N];

inline ll pow_mod(ll x, ll y)
{
    long long ans = 1;
    while (y)
    {
        if (y & 1)
        {
            ans = (ans * x) % MOD;
            y--;
        }
        y /= 2;
        x = x * x % MOD;
    }
    return ans;
}
bool cmp(H &a, H &b)
{
    if (a.hash == b.hash)
    {
        if (a.hash2 == b.hash2)
        {
            return a.k < b.k;
        }
        return a.hash2 < b.hash2;
    }
    return a.hash < b.hash;
}
void rollinghash(char *s)
{
    int len = strlen(s);

    ll p1 = 19260817LL;
    ll p2 = 13131317LL;
    ll tmp = 0;
    ll tmp2 = 0;
    for (int i = 0; i < len; i++)
    {
        tmp = ((tmp * p1) % MOD + s[i]) % MOD;
        tmp2 = ((tmp2 * p2) % MOD + (s[i])) % MOD;
        _hash[i].k = i;
    }

    _hash[0].hash = tmp;
    _hash[0].hash2 = tmp2;

    tmp = pow_mod(p1, len - 1) % MOD;
    tmp2 = pow_mod(p2, len - 1) % MOD;

    for (int i = 1; i < len; i++)
    {
        _hash[i].hash = (_hash[i - 1].hash - (tmp * s[i - 1]) % MOD + MOD) % MOD;
        _hash[i].hash = (_hash[i].hash * p1) % MOD;
        _hash[i].hash += s[i + len - 1];
        _hash[i].hash %= MOD;

        _hash[i].hash2 = (_hash[i - 1].hash2 - (tmp2 * s[i - 1]) % MOD + MOD) % MOD;
        _hash[i].hash2 = (_hash[i].hash2 * p2) % MOD;
        _hash[i].hash2 += s[i + len - 1];
        _hash[i].hash2 %= MOD;
    }

    sort(_hash, _hash + len, cmp);
    _hash[len].hash = -1;
    _hash[len].hash2 = -1;
}
int main() {}
