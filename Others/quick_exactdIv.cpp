//在[1e10 + 1,1e10 + 2*1e5]区间内素数判定
//8-9倍速度   4.152 s / 0.415 s
using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;
 
template <typename T>
struct ExactDiv {
  ExactDiv() {}
  ExactDiv(T n) : t(T(-1) / n), i(mul_inv(n)) {}   //初始化除数
  T mul_inv(T n) {
    T x = n;
    for (int i = 0; i < 5; ++i) x *= 2 - n * x;
    return x;
  }
  friend T operator / (T n, ExactDiv d) { return n * d.i; }; 
  bool divide(T n) { return n * this->i <= this->t; }    //测试n是否被整除
  T t, i;
};
 