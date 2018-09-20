
struct edge{
    int v,nxt;
};
const int N = 1000+5;//nodes
const int M = 1000000+5;//edges

struct Hungary{
    int pre[N],mcnt;
    edge e[M];
    int cy[N];
    bool vis[N];
    void init(){
        mem(pre,-1);mcnt=0;
        mem(cy,-1);
    }
    void addarc(int x,int y){
        e[mcnt] = (edge){y, pre[x]}, pre[x]=mcnt++;
    }
    bool check(int u) {
        for (int i = pre[u]; ~i; i = e[i].nxt) {
            int v = e[i].v;
            if (vis[v]) continue;
            vis[v] = true;
            if (cy[v] == -1 || check(cy[v])) {
                cy[v] = u;
                return true;
            }
        }
        return false;
    }
    int go(int n) {
        int ret = 0;
        for (int i = 1; i <= n; ++i) {
            mem(vis,0);
            ret += check(i);
        }
        return ret;
    }
}solver;