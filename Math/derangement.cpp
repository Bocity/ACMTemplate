ll f[N];
void getDerange(int n){
  f[0] = 1;f[1] = 0;
  for(int i=2;i<n+1;++i) f[i] = (i-1)*(f[i-1]+f[i-2])%MOD;
}

double p[N];
void getDerangeP(int n){
  p[0] = 1;p[1] = 0;
  double po = 1, sgn = -1;
  for(int i=2;i<n+1;++i) {
    sgn*=-1;po*=i;
    p[i] = p[i-1]+1/po*sgn;
  }
}