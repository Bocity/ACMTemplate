__builtin_ffs(x)：返回x中最后一个为1的位是从后向前的第几位,__builtin_ffs(x) - 1就是x中最后一个为1的位的位置。
__builtin_popcount(x)：x中1的个数。
__builtin_ctz(x)：x末尾0的个数。x=0时结果未定义。 
__builtin_clz(x)：x前导0的个数。x=0时结果未定义。
__builtin_parity(x)：x中1的奇偶性。
