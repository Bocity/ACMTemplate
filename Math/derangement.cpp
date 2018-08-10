ll f[N];
void getDerange(int n){
  f[0] = 1;f[1] = 0;
  for(int i=2;i<n+1;++i) f[i] = (i-1)*(f[i-1]+f[i-2])%MOD;
  // for(int i=2;i<n+1;++i) cout<<f[i]<<" ";cout<<endl;
}