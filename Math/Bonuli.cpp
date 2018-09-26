ll addp(ll x,ll y,ll p = MOD){return x+y>=p?x+y-p:x+y;}
ll modp(ll x,ll p = MOD){return addp(x%p,p,p);} //常数较大

ll inv[1500];
void init2(){
  inv[1] = 1;
  for (int i = 2; i <= 1200; i++) inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
}
ll C[1200][1200];
void init() {
    C[0][0] = 1;
    for (int i = 1; i <= 1100; i++) {
        for (int j = 0; j <= i; j++) {
            C[i][j] = ((ll) C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }
}
ll B[2000];
void init3(){
  B[0] = 1;
  llp(n,1,1050){
    B[n] = 0;
    llp(k,0,n) B[n] = addp(B[n] , C[n+1][k]*B[k]%MOD);
    B[n] = modp(B[n]*(-inv[n+1]));
  }
}
ll Bi(ll n,ll k){
  ll ans = 0;
  ll po = 1;
  llp(i,1,k+2) {
    po = po*(n+1)%MOD;//(n+1)^i
    ans = addp( ans , C[k+1][i]*B[k+1-i]%MOD*po%MOD );
  }
  ans = ans * inv[k+1]%MOD;
  return ans;
}