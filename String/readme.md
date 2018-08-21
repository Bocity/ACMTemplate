# String
## shift-and
处理每个字符位多字符匹配的问题。模板题：hdu

利用位运算来实现并行。bst_b存储的是字符集里每个字符的合法的位置，bst_d用来维护并行匹配状态的进度。

需要更改的地方：
- 匹配bitset的范围
- 匹配bitset的初始赋值
- 与运算


##最小循环节
KMP最小循环节、循环周期：

定理：假设S的长度为len，则S存在最小循环节，循环节的长度L为len-next[len]，子串为S[0…len-next[len]-1]。

（1）如果len可以被len - next[len]整除，则表明字符串S可以完全由循环节循环组成，循环周期T=len/L。

（2）如果不能，说明还需要再添加几个字母才能补全。需要补的个数是循环个数L-len%L=L-(len-L)%L=L-next[len]%L