struct node{  
    int to,next;ll c;  
}e[N*2];
int cnt=0;  
int first[N];
void insert(int u,int v,ll c){  
    e[++cnt] = node{v,first[u],c};first[u]=cnt;  
    e[++cnt] = node{u,first[v],c};first[v]=cnt;  
}  
for(int k=first[x];k;k=e[k].next)  
    if(!visit[e[k].to])  
    {  
        dfs(e[k].to);  
        size[x]+=size[e[k].to];  
    }  
