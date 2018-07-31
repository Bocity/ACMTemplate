int fa[20001];
int find(int x) //用于查找一个元素的所在集合即根节点
{
    if (fa[x] != x) fa[x] = find(fa[x]); //路径压缩，递归将路径上的元素父亲指针都指向根节点
    return fa[x];
}
void merge(int r1, int r2) //合并两个集合，r2合并到r1
{
    r1 = find(r1);
    r2 = find(r2);
    if (r1 != r2) fa[r2] = r1;
}
