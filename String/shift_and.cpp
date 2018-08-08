// char版本
// Shift_and 匹配字符串

#include <bitset>
//#pragma comment(linker, "/STACK:1024000000,1024000000")
bitset<1005> bst_b[128]; //按照题目要求更换，模式串字符数，需修改
// s为目标串 p为模式串
bitset<1005> bst_d;//用来储存匹配的bitset
int shift_and(char s[], int len_s) { 
    bst_d.reset();
    for (int i = 0; i < len_s; i++) {
        bst_d = bst_d << 1;
        bst_d.set(0);                      //将第一位设置为1
        bst_d = bst_d & bst_b[s[i] - '0']; //判断当前字符是否合法，需修改
        if (bst_d[n - 1] == 1) {
            // 输出字符串
            // char tmp = s[i + 1];
            // s[i + 1] = '\0';
            // cout << s + i + 1 - len_p << endl;
            // s[i + 1] = tmp;
            return s + i - n + 1; //返回找到的字符串首地址，若有多个可以储存到vector中
        }
    }
    return 0;
}
char mode[1005];
char strr[1005];
int main() {
    ios::sync_with_stdio(false);
    while (cin >> n) {
        for (int i = 0; i < 128; i++) bst_b[i].reset();  //初始化bitset
        scanf("%s %s",p,s);

        int len = strlen(p);
        for (int i = 0; i < len; i++) bst_b[p[i]-'0'].set(); //赋值模式bitset，需修改

        shift_and(sstr, strlen(sstr));
    }
    return 0;
}
