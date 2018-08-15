//一堆石子，轮流取[p,q]个，先手必胜返回true
bool as(int n, int p, int q)
{
    if (!((n % (p + q) != 0) && ((n % (p + q)) <= p)))
        return 1;
    else
        return 0;
}
