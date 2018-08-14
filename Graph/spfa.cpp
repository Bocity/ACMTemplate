struct arc {
    int x, f, next;
};
const int N = 10000;//nodes
const int M = 100000;//edges

// normal
struct spfa {
    int pre[N], mcnt, s, dis[N];
    bool vis[N];
    arc e[2 * M];
    void init(int i) {
        mems(pre, -1);
        mcnt = 0;
        s = i;
    }
    void addarc(int x, int y, int z) {
        e[mcnt] = (arc){y, z, pre[x]}, pre[x] = mcnt++;
        e[mcnt] = (arc){x, z, pre[y]}, pre[y] = mcnt++;
    }
    void go() {
        queue<int> q;
        mems(dis, 0x3f);
        mems(vis, false);
        dis[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = false;
            for (int i = pre[u]; ~i; i = e[i].next) {
                int v = e[i].x, c = e[i].f;
                
                if (dis[v] > dis[u] + c) {
                    dis[v] = dis[u] + c;
                    if (!vis[v]) vis[v] = true, q.push(v);
                }
            }
        }
    }
};


// SLF优化(Small Label First)
struct spfa {
    int pre[N], mcnt, s, dis[N];
    bool vis[N];
    arc e[2 * M];
    void init(int i) {
        mems(pre, -1);
        mcnt = 0;
        s = i;
    }
    void addarc(int x, int y, int z) {
        e[mcnt] = (arc){y, z, pre[x]}, pre[x] = mcnt++;
        e[mcnt] = (arc){x, z, pre[y]}, pre[y] = mcnt++;
    }
    void go() {
        deque<int> q;
        mems(dis, 0x3f);
        mems(vis, false);
        dis[s] = 0;
        q.push_back(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            vis[u] = false;
            for (int i = pre[u]; ~i; i = e[i].next) {
                int v = e[i].x, c = e[i].f;
                if (dis[v] > dis[u] + c) {
                    dis[v] = dis[u] + c;
                    if (!vis[v]){
                        vis[v] = true;
                        if (dis[v] < dis[q.front()]) q.push_front(v);
                        else q.push_back(v);
                    } 
                }
            }
        }
    }
};

// LLF优化(Large Label Last)
