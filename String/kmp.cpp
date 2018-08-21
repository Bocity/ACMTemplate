int nextt[N];
void getNext(char *s)
{
    int len = strlen(s), k = -1, j = 0;
    nextt[0] = -1;
    while (j < len)
    {
        if (k == -1 || s[j] == s[k])
        {
            j++, k++;
            nextt[j] = k;
        }
        else
            k = nextt[k];
    }
}
//S为文本串，P为模式串

//返回第一次匹配位置，失配为-1
//选择返回cnt时 为匹配次数
int match(char *s, char *p)
{
    int cnt = 0;
    int lenS = strlen(s);
    int lenP = strlen(p);
    int j = 0, k = 0;
    while (k < lenP && j < lenS)
    {
        if (k == -1 || s[j] == p[k])
        {
            j++, k++;
        }
        else
            k = nextt[k];
        // if (k == lenP) {
        //     cnt++;
        //     k = nextt[k]; //k=0 不重叠
        // }
    }
    if (k < lenP)
        return -1;
    else
        return j - lenP;
    //return cnt;
}