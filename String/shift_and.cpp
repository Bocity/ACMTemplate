//跑得很快的板子
char P[2000], T[2000];
bitset<1000> B[256], D; // B数组大小为字符的种数,长度为MXP
void pre_solve(char P[]) {
    int len = strlen(P);
    D.reset();
    for (int i = 0; i < 256; i++) B[i].reset();
    for (int i = 0; i < len; i++) B[P[i]].set(i);
}
int shift_and(char T[]) {
    int len = strlen(T);
    // pre_solve(P);
    for (int i = 0; i < len; i++) {
        D = (D << 1).set(0) & B[T[i]-'0'];  //修改
        if (D[n - 1]) {
            //输出字符串，puts贼快
            char ch = T[i + 1];
            T[i + 1] = 0;
            puts(T + i - n + 1);
            T[i + 1] = ch;
        }
    }
    return -1;
}


