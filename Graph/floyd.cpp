#define REP(i,a,b) for(int i=a;i<b;++i)
#define mem(a,x) memset(a,x,sizeof a)

const int N = 1000;

int dp[N][N];
mem(dp)
REP(i,1,n+1) REP(j,1,n+1) dp[i][j]  = min(dp[i][k]+dp[k][j], dp[i][j]);
REP(k,1,n+1) REP(i,1,n+1) REP(j,1,n+1) dp[i][j]  = min(dp[i][k]+dp[k][j], dp[i][j]);