//判断n是否是平方数
int m = sqrt(n)+0.5;
if(m*m==n)
    return true;

//解出n  n*(n+1)/2 <= x < (n+1)*(n+2)/2，即自然数前n项和不超过x的最大的n
ll n = sqrt(2*x);  //sqrt(2*x)可能为n或n+1
while( x < n*(n+1)/2 ) n--; //排除n+1

//若方程为：n*(n+1)/2 < x <= (n+1)*(n+2)/2，即自然数前n项和小于x的最大的n
ll n = sqrt(2*x);  //sqrt(2*x)可能为n或n+1
while( x <= n*(n+1)/2 ) n--; //排除n+1


//判断平方数的O(n)方法，正方形数
for(int i=1;n>0;i+=2)  
      n-=i;   
return 0==n;  