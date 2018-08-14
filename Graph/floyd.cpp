const int N = 1000;
int dp[N][N];//初始值：邻接矩阵
void floyd(){
  REP(k,1,n+1) REP(i,1,n+1) REP(j,1,n+1) 
    dp[i][j]  = min(dp[i][k]+dp[k][j], dp[i][j]);
}