// X=a[n]*(n-1)!+a[n-1]*(n-2)!+...+a[i]*(i-1)!+...+a[1]*0! 
// 其中, a[i]为整数，并且0 <= a[i] <= i, 0 <= i < n, 表示当前未出现的的元素中排第几个，这就是康托展开。
// 再举个例子说明。 
// 在（1，2，3，4，5）5个数的排列组合中，计算 34152的康托展开值。
// 首位是3，则小于3的数有两个，为1和2，a[5]=2，则首位小于3的所有排列组合为 a[0]*(5-1)!
// 第二位是4，则小于4的数有两个，为1和2，注意这里3并不能算，因为3已经在第一位，所以其实计算的是在第二位之后小于4的个数。因此a[4]=2
// 第三位是1，则在其之后小于1的数有0个，所以a[3]=0
// 第四位是5，则在其之后小于5的数有1个，为2，所以a[2]=1
// 最后一位就不用计算啦，因为在它之后已经没有数了，所以a[1]固定为0
// 根据公式： 
// X = 2 * 4! + 2 * 3! + 0 * 2! + 1 * 1! + 0 * 0! 
// = 2 * 24 + 2 * 6 + 1 
// = 61 
// 所以比 34152 小的组合有61个，即34152是排第62。
static const int FAC[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};   // 阶乘
int cantor(int *a, int n)
{
    int x = 0;
    for (int i = 0; i < n; ++i) {
        int smaller = 0;  // 在当前位之后小于其的个数
        for (int j = i + 1; j < n; ++j) {
            if (a[j] < a[i])
                smaller++;
        }
        x += FAC[n - i - 1] * smaller; // 康托展开累加
    }
    return x;  // 康托展开值
}
// 这里主要为了讲解康托展开的思路，实现的算法复杂度为O(n^2)，实际当n很大时，内层循环计算在当前位之后小于当前位的个数可以用 线段树来处理计算，而不用每次都遍历，这样复杂度可以降为O(nlogn)。
// 一开始已经提过了，康托展开是一个全排列到一个自然数的双射，因此是可逆的。即对于上述例子，在（1，2，3，4，5）给出61可以算出起排列组合为 34152。由上述的计算过程可以容易的逆推回来，具体过程如下：
// 用 61 / 4! = 2余13，说明a[5]=2,说明比首位小的数有2个，所以首位为3。
// 用 13 / 3! = 2余1，说明a[4]=2，说明在第二位之后小于第二位的数有2个，所以第二位为4。 
// 用  1 / 2! = 0余1，说明a[3]=0，说明在第三位之后没有小于第三位的数，所以第三位为1。
// 用  1 / 1! = 1余0，说明a[2]=1，说明在第二位之后小于第四位的数有1个，所以第四位为5。
// 最后一位自然就是剩下的数2啦。
// 通过以上分析，所求排列组合为 34152。
static const int FAC[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};   // 阶乘

//康托展开逆运算
void decantor(int x, int n)
{
    vector<int> v;  // 存放当前可选数
    vector<int> a;  // 所求排列组合
    for(int i=1;i<=n;i++)
        v.push_back(i);
    for(int i=m;i>=1;i--)
    {
        int r = x % FAC[i-1];
        int t = x / FAC[i-1];
        x = r;
        sort(v.begin(),v.end());// 从小到大排序 
        a.push_back(v[t]);      // 剩余数里第t+1个数为当前位
        v.erase(v.begin()+t);   // 移除选做当前位的数
    }
}
// 给定一个自然数集合组合一个全排列，所其中的一个排列组合在全排列中从大到小排第几位。 
// 在上述例子中，在（1，2，3，4，5）的全排列中，34152的排列组合排在第62位。
// 反过来，就是逆康托展开，求在一个全排列中，第n个全排列是多少。 
// 比如求在（1，2，3，4，5）的全排列中，第62个排列组合是34152。[注意具体计算中，要先 -1 才是其康托展开的值。]
// 另外康托展开也是一个数组到一个数的映射，因此也是可用于hash，用于空间压缩。比如在保存一个序列，我们可能需要开一个数组，如果能够把它映射成一个自然数， 则只需要保存一个整数，大大压缩空间。比如八数码问题。
