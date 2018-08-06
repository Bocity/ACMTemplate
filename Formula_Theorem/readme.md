## Lindström–Gessel–Viennotr-lemma
对于一张无边权的DAG图，给定n个起点和对应的n个终点，这n条不相交的路径的方案数为

\\[
det (\left|\begin{array}{cccc} 
    e(a_1,b_1) &    e(a_1,b_2)    & ... & e(a_1,b_n) \\ 
    e(ai,b1) &  e(ai,b2)  & ... & e(ai,bn)\\ 
    e(an,b1) & e(an,b2) & ... & e(an,bn) 
\end{array}\right|)
\\]

其中e(a,b)为a到b的方案数
网格图亦可

## 判断C（n,m）奇偶性

\\((n \& m) == m\\)


## 与某树同构期望
子树大小倒数乘积
## 删子树轮数期望
结点深度倒数和
## Johnson法则
```cpp
bool cmp(node x, node y) {
    if (min(y.l, x.r) == min(x.l, y.r)) return x.l > y.l;
    return min(y.l, x.r) < min(x.l, y.r);
}
```
## 欧拉降幂
$
A^K \equiv \left \{
\begin{aligned}
& A^{K \%\phi(m)}  &  \gcd(A,K)=1\\
& A^{K \%\phi(m) +\phi(m)}    & \gcd(A,K) \neq 1, K \geq  \phi(m) \\
& A^{K}   & \gcd(A,K) \neq 1, K <  \phi(m) 
\end{aligned} 
\right.
\qquad
(\ mod\ m)
$
## 绝对值不等式
$||a|-|b|| ≤|a±b|≤|a|+|b|$
## able 变换
$\sum _{{k=m}}^{n}f_{k}(g_{{k+1}}-g_{k})=\left[f_{{n+1}}g_{{n+1}}-f_{m}g_{m}\right]-\sum _{{k=m}}^{n}g_{{k+1}}(f_{{k+1}}-f_{k}).$

$\sum _{{i=m+1}}^{n}\left(b_{i}-b_{{i-1}}\right)a_{i}+\sum _{{i=m+1}}^{n}\left(a_{i}-a_{{i-1}}\right)b_{{i-1}}=a_{n}b_{n}-a_{m}b_{m}=\sum _{{i=m+1}}^{n}\left(b_{i}-b_{{i-1}}\right)a_{{i-1}}+\sum _{{i=m+1}}^{n}\left(a_{i}-a_{{i-1}}\right)b_{i}$