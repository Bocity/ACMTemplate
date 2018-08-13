#include <bits/stdc++.h>
#define REP(i,x,n) for(int i = (x); i < (n); ++i)

// 矩阵快速幂
const ll MOD = 1e9+7;
const int N = 3;
struct Mat {
    ll mat[N][N]; 
    Mat{memset(mat,0,sizeof mat);}
};
Mat operator*(Mat a, Mat b) {
    Mat c;
    REP(k,0,N) REP (i,0,N)  REP (j,0,N)             
        c.mat[i][j] = (c.mat[i][j] + a.mat[i][k] * b.mat[k][j]) % MOD;
    return c;
}
Mat operator^(Mat a, ll k) {
    Mat c;
    REP(i,0,N) REP(j,0,N) c.mat[i][j] = (i == j);
    for (; k; k >>= 1) {
        if (k & 1) c = c * a;
        a = a * a;
    }
    return c;
}

int t,n;
Mat a,b,c,d,e;
int main(){
    ios::sync_with_stdio();
    cin.tie(0);
    a.mat[0][0] = 2,a.mat[0][1] = 2,a.mat[0][2] = 3;
    a.mat[1][0] = 1,a.mat[1][1] = 0,a.mat[1][2] = 0;
    a.mat[2][0] = 0,a.mat[2][1] = 0,a.mat[2][2] = 1;
    b.mat[0][0] = 0,b.mat[1][0] = 1,b.mat[2][0] = 1;
    c.mat[0][0] = 0,c.mat[1][0] = 2,c.mat[2][0] = 1; 
    cin >> t;
    while(t--){
        cin >> n;
        d = (a^n) * b;
        e = (a^n) * c;
        cout << d[0][0] << " " << e[0][0] << endl;
    }
    return 0;
}
// Q0 = 0 Q1 = 1 Q2 = 5
// R0 = 0 R1 = 2 R2 = 7
// Qn = 2Qn-1+2Qn-2+3
// Rn = 2Rn-1+2Rn-2+3
//[2,2,3]*[Qn-1,Qn-2,1]^T
//[1,0,0]
//[0,0,1]

