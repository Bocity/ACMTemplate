
struct E {
    int from, to, cap, flow;
    E() {}
    E(int f, int t, int c, int fl)
        : from(f)
        , to(t)
        , cap(c)
        , flow(fl) {}
};

struct Dinic {
    int n, m, s, t;
    vector<E> e;
    vector<int> G[maxn];
    bool vis[maxn];
    int cur[maxn];
    int d[maxn];
    const int INF = 1 << 29;
    void init(int n, int s, int t) {
        this->n = n, this->s = s, this->t = t;
        e.clear();
        for (int i = 0; i < n; ++i) G[i].clear();
    }

    void add(int from, int to, int cap) {
        e.push_back(E(from, to, cap, 0));
        e.push_back(E(to, from, 0, 0));
        m = e.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }

    bool bfs() {
        queue<int> Q;
        memset(vis, 0, sizeof(vis));
        vis[s] = true;
        d[s] = 0;
        Q.push(s);
        while (!Q.empty()) {
            int x = Q.front();
            Q.pop();
            for (int i = 0; i < G[x].size(); ++i) {
                E &ed = e[G[x][i]];
                if (!vis[ed.to] && ed.cap > ed.flow) {
                    vis[ed.to] = true;
                    d[ed.to] = d[x] + 1;
                    Q.push(ed.to);
                }
            }
        }
        return vis[t];
    }

    int dfs(int x, int a) {
        if (x == t || a == 0) return a;
        int flow = 0, f;
        for (int &i = cur[x]; i < G[x].size(); ++i) {
            E &ed = e[G[x][i]];
            if (d[ed.to] == d[x] + 1 && (f = dfs(ed.to, min(a, ed.cap - ed.flow))) > 0) {
                ed.flow += f;
                e[G[x][i] ^ 1].flow -= f;
                flow += f;
                a -= f;
                if (a == 0) break;
            }
        }
        return flow;
    }

    int max_flow() {
        int ans = 0;
        while (bfs()) {
            memset(cur, 0, sizeof(cur));
            ans += dfs(s, INF);
        }
        return ans;
    }
} DC;
