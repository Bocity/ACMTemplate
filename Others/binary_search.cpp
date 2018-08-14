// 二分：1.答案具有单调性 2.验证答案复杂度不高
// 单调性：e.p. 若x满足条件，则a>x也满足条件

// 整数（感谢c老师）
// 单调左（答案左边都可以），lrr, r<l
int l = 1, r = n;
while(l<=r){
  int mid = (l+r)/2;
  if (check(mid)) l = mid+1;
  else r = mid-1;
}
ans = r;
assert(1<=r);
// 单调右（答案右边都可以）, rll, l>r
int l = 1, r = n;
while(l<=r){
  int mid = (l+r)/2;
  if (check(mid)) r = mid-1;
  else l = mid+1;
}
ans = l;
assert(l<=n);

// 小数
// 固定精度
const double eps = 1e-7;
double l = 1, r = 10000;
while(l+eps < r){
  double mid = (l+r)/2;
  if (check(mid)) l = mid;
  r = mid;
}
// 固定次数
int t=1000;
double l = 1, r = 10000;
while(t--){
  double mid = (l+r)/2;
  if (check(mid)) l = mid;
  r = mid;
}


// 三分：极值点左右严格
// 不严格不行
// l和r需要在最值的左右，如果落在最值上，不管怎么写都有漏解的情况。
// 如最值连续相等，=则落在最左边，不=则落在最右边
int SanFen(int l,int r) //找凸点  mid > mmid
{  
    while(l < r-1)  
    {  
        int mid  = (l+r)/2;  
        int mmid = (mid+r)/2;  
        if( f(mid) > f(mmid) )  
            r = mmid;  
        else  
            l = mid;  
    }  
    return f(l) > f(r) ? l : r;  
}  

int SanFen(int l,int r) //找凹点  mid<mmid
{  
    while(l < r-1)  
    {  
        int mid  = (l+r)/2;  
        int mmid = (mid+r)/2;  
        if( f(mid) < f(mmid) )  
            r = mmid;  
        else  
            l = mid;  
    }  
    return f(l) < f(r) ? l : r;  
}  