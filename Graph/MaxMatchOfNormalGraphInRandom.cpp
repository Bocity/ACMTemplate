#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;

const int N = 400 + 5;

int n, m;
ll wnn[N][N];

bool instk[N];
ll dn[N];
int match[N], stk[N], bs;

int qn[N];

bool dfs(int u) {
	stk[++bs] = u;
	if(instk[u]) return true;
	instk[u] = true;
	for(int vt = 1; vt <= n; ++vt) {
		int v = qn[vt];
		if(!instk[v] && v != u && v != match[u]) {
			ll d = dn[u] + wnn[u][v] - wnn[v][match[v]];
			if(d <= dn[match[v]]) continue;
			dn[match[v]] = d;
			if(dfs(match[v])) return true;
		}
	}
	--bs;
	instk[u] = false;
	return false;
}

int pn[N];

inline ll solve() {
	for(int i = 1; i <= n; i += 2) match[i] = i + 1, match[i + 1] = i;
	for(int i = 1; i <= n; ++i) pn[i] = qn[i] = i;
	for(int cnt = 1; cnt <= 3; ++cnt) {
		random_shuffle(pn + 1, pn + n + 1);
		random_shuffle(qn + 1, qn + n + 1);
		bool did = true;
		while(did) {
			did = false;
			memset(instk, 0, sizeof(instk));
			memset(dn, 0, sizeof(dn));
			bs = 0;
			for(int j = 1; j <= n; ++j) if(dfs(pn[j])) {
				did = true;
				--bs;
				int bt = bs;
				while(stk[bt] != stk[bs + 1]) --bt;
				int m1 = match[stk[bt]];
				for(int i = bt; i <= bs - 1; ++i) match[stk[i]] = match[stk[i + 1]];
				match[stk[bs]] = m1;
				for(int i = bt; i <= bs; ++i) match[match[stk[i]]] = stk[i];
				break;
			}
		}
	}
	ll ans = 0;
	for(int i = 1; i <= n; ++i) if(i < match[i]) ans += wnn[i][match[i]];
	return ans;
}

int bematched[N];

inline void check() {
	for(int i = 1; i <= n; ++i) ++bematched[match[i]];
	for(int i = 1; i <= n; ++i) if(bematched[i] >= 2) throw 233;
	for(int i = 1; i <= n; ++i) if(match[match[i]] != i) throw 233.;
}

int main() {
	scanf("%d%d", &n, &m);
	while(m--) {
		int u, v; ll w; scanf("%d%d%lld", &u, &v, &w);
		wnn[u][v] = max(wnn[u][v], w);
		wnn[v][u] = max(wnn[v][u], w);
	}
	int n0 = n;
	if(n & 1) ++n;
	printf("%lld\n", solve());
	for(int i = 1; i <= n0; ++i) printf("%d%c", (!wnn[i][match[i]] ? 0 : match[i]), " \n"[i == n0]);
	return 0;
}
