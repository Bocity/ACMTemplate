//  划分元素可重复任意次
#define f(x) (((x) * (3 * (x) - 1)) >> 1)
#define g(x) (((x) * (3 * (x) + 1)) >> 1)

const int MAXN = 1e5 + 10;
const int MOD = 1e9 + 7;

int n, ans[MAXN];

int main()
{
    scanf("%d", &n);

    ans[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; f(j) <= i; ++j)
        {
            if (j & 1)
            {
                ans[i] = (ans[i] + ans[i - f(j)]) % MOD;
            }
            else
            {
                ans[i] = (ans[i] - ans[i - f(j)] + MOD) % MOD;
            }
        }
        for (int j = 1; g(j) <= i; ++j)
        {
            if (j & 1)
            {
                ans[i] = (ans[i] + ans[i - g(j)]) % MOD;
            }
            else
            {
                ans[i] = (ans[i] - ans[i - g(j)] + MOD) % MOD;
            }
        }
    }

    printf("%d\n", ans[n]);

    return 0;
}

// 整数划分（五边形定理拓展）
// F(n, k) = P(n) - 划分元素重复次数≥k次的情况。
//  问一个数n能被拆分成多少种情况
//  且要求拆分元素重复次数不能≥k
const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 10;

int ans[MAXN];

//  此函数求ans[]效率比上一个代码段中求ans[]效率高很多
void init()
{
    memset(ans, 0, sizeof(ans));

    ans[0] = 1;
    for (int i = 1; i < MAXN; ++i)
    {
        ans[i] = 0;
        for (int j = 1; ; j++)
        {
            int tmp = (3 * j - 1) * j / 2;
            if (tmp > i)
            {
                break;
            }
            int tmp_ = ans[i - tmp];
            if (tmp + j <= i)
            {
                tmp_ = (tmp_ + ans[i - tmp - j]) % MOD;
            }
            if (j & 1)
            {
                ans[i] = (ans[i] + tmp_) % MOD;
            }
            else
            {
                ans[i] = (ans[i] - tmp_ + MOD) % MOD;
            }
        }
    }

    return ;
}

int solve(int n, int k)
{
    int res = ans[n];
    for (int i = 1; ; i++)
    {
        int tmp = k * i * (3 * i - 1) / 2;
        if (tmp > n)
        {
            break;
        }
        int tmp_ = ans[n - tmp];
        if (tmp + i * k <= n)
        {
            tmp_ = (tmp_ + ans[n - tmp - i * k]) % MOD;
        }
        if (i & 1)
        {
            res = (res - tmp_ + MOD) % MOD;
        }
        else
        {
            res = (res + tmp_) % MOD;
        }
    }
    return res;
}

int main(int argc, const char * argv[])
{
    init();

    int T, n, k;

    cin >> T;
    while (T--)
    {
        cin >> n >> k;
        cout << solve(n, k) << '\n';
    }

    return 0;
}

