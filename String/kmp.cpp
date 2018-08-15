#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int nextt[N];
void getNext(string &str)
{
    int len = str.size(), k = -1, j = 0;
    nextt[0] = -1;
    while (j < len)
    {
        if (k == -1 || str[j] == str[k])
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
int match(string &S, string &P)
{
    int cnt = 0;
    int lenS = S.size();
    int lenP = P.size();
    int j = 0, k = 0;
    while (k < lenP && j < lenS)
    {
        if (k == -1 || S[j] == P[k])
        {
            j++, k++;
        }
        else
            k = nextt[k];
        // if (k == lenP) {
        //     cnt++;
        //     k = nextt[k]; //重叠
        ////k=0; //不重叠
        // }
    }
    if (k < lenP)
        return -1;
    else
        return j - lenP;
    //return cnt;
}