void build(int n) {
    for (int i = 1; i <= n; ++i) {
        d[i].val = a[i];
        d[i].l = 0;
        d[i].r = 0;
        d[i].f = 0;
    }
    int top = 1;
    stack[top] = 1;
    for (int i = 2; i <= n; i++) {
        while (top > 0 && d[i].val < d[stack[top]].val) //小根堆则改成小于
            top--;
        if (top > 0) // 右链中的节点
        {
            d[i].f = stack[top];
            d[i].l = d[stack[top]].r;
            d[d[stack[top]].r].f = i;
            d[stack[top]].r = i;
            stack[++top] = i;
        } else // 根节点
        {
            d[stack[1]].f = i;
            d[i].l = stack[1];
            stack[++top] = i;
        }
    }
    dfs(stack[1]);
}
