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
## 邻接矩阵性质
邻接矩阵的k次幂的第 i 行 j 列就表示从 i 正好走 k 步到 j 的方案数。
## 斐波那契数列循环节
1. 对于与5互质的质数p，如果5是模p的二次剩余，那么模p意义下的循环节长度是(p-1)的因子。 
2. 对于与5互质的质数p，如果5是模p的二次非剩余，那么模p意义下的循环节长度是(2p+2)的因子。 
3. 对于模质数的幂p^k意义下的循环节，其值为模p意义下的循环节长度乘p^(k-1)。 
4. 对于模x意义下的循环节，如果x被质因数分解为p1^k1*p2^k2*…*pm^km，则循环节是模每个质数的幂意义下的循环节的最小公倍数。
5. 特别的  loop(2)=3,loop(3)=8,loop(5)=20。
## 广义斐波那契数列循环节
斐波那契数列作为广义斐波那契数列f(n)=a*f(n-1)+b*f(n-2)的一个特殊情况在模素数p的最小循环节len满足以下结论（其中c=a^2+4*b^2=5） 
1.当c是模p的二次剩余时，最小循环节是p-1的因子 
2.当c不是模p的二次剩余时，最小循环节是(p-1)(p+1)的因子 
3.当c=p时，结论不定，此处暴力找一下可以知道p=5时最小循环节是20 