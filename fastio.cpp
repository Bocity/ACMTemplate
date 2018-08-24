// maxlen 输出单位长度（只影响速度，不用改）
// xchar/wchar 读入/输出字符，基本函数
// xint/wint，读入/输出符号整数(ll)
// xstring/wstring，读入/输出char字符串

typedef long long ll;
typedef long long ull;
const int maxlen = 100000;
struct FastIO {
    static const int S = 2*maxlen;
    int wpos;
    char wbuf[S];
    FastIO() : wpos(0) {}
    inline int xchar() {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len) pos = 0, len = fread(buf, 1, S, stdin);
        if (pos == len) return 0;
        return buf[pos++];
    }
    inline bool xint(auto &x) {
        int s = 1, c = xchar();x = 0;
        while (c && c <= 32) c = xchar();
        if (c == '-') s = -1, c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        x*=s;
        return c;
    }
    inline bool xstring(char *s) {
        int c = xchar();
        while (c && c <= 32) c = xchar();
        for (; c > 32; c = xchar()) *s++ = c;
        *s = 0;
        return c;
    }
    inline void wchar(int x) {
        if (wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
        wbuf[wpos++] = x;
    }
    inline void wint(auto x) {
        if (x < 0) wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
    }
    inline void wstring(const char *s) {
        while (*s) wchar(*s++);
    }
    inline void wln() {
        wchar('\n');
    }
    ~FastIO() {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;