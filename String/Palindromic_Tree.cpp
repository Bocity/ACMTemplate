
struct Palindromic_Tree
{
    int ch[N][26], fail[N];
    int cnt[N];     // 当前节点表示回文串的个数
    int num[N];     // 当前节点表示回文串中的后缀子回文串的个数(包括自己)
    int len[N];     // 当前节点表示的回文串的长度
    int S[N];       // 存放添加的字符
    int last, n, p; // p节点个数 n字符串长度

    int newnode(int l)
    {
        memset(ch[p], 0, sizeof ch[p]);
        cnt[p] = 0;
        num[p] = 0;
        len[p] = l;
        return p++;
    }

    void init()
    {
        p = 0;
        newnode(0);
        newnode(-1);
        last = 0;
        n = 0;
        S[n] = -1; //开头放一个字符集中没有的字符，减少特判
        fail[0] = 1;
    }

    int get_fail(int x)
    { //和KMP一样，失配后找一个尽量最长的
        while (S[n - len[x] - 1] != S[n])
            x = fail[x];
        return x;
    }

    int add(int c)
    { //返回以当前字符结尾的回文串个数
        S[++n] = c;
        int cur = get_fail(last); //通过上一个回文串找这个回文串的匹配位置
        if (!ch[cur][c])
        {                                           //如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
            int now = newnode(len[cur] + 2);        //新建节点
            fail[now] = ch[get_fail(fail[cur])][c]; //和AC自动机一样建立fail指针，以便失配后跳转
            ch[cur][c] = now;
            num[now] = num[fail[now]] + 1;
        }
        last = ch[cur][c];
        cnt[last]++;
        return num[last];
    }

    void count()
    {
        for (int i = p - 1; i >= 0; --i)
            cnt[fail[i]] += cnt[i];
        //父亲累加儿子的cnt，因为如果fail[v]=u，则u一定是v的子回文串！
    }
    void build(char *s)
    {
        init();
        for (int i = 0; s[i]; ++i)
            add(s[i] - 'a');
        count();
    }
    void build(int *s, int l)
    {
        init();
        for (int i = 0; i < l; ++l)
            add(s[i]);
        count();
    }
} pt;