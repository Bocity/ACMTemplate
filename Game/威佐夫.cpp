bool as(int n, int m)
{
    if (n < m)
        swap(n, m);
    int k = n - m;
    n = (int)(k * (1 + sqrt(5)) / 2.0);
    if (n == m)
        return 0;
    else
        return 1;
}

//打表
map<int, int> p;
void init()
{
    double s = ((1 + sqrt(5)) / 2.0);
    for (int i = 0; i < 381967; i++)
    {
        int a = i * s;
        int b = a + i;
        p[b] = a;
        p[a] = b;
    }
}