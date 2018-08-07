//Matters Computational p765 证明方法
//2.755 s / 1.398 s
// 32位机器 。。。结果可能有危险
using i64 = long long;
using u64 = unsigned long long;
using f80 = long double;

inline u64 mul_mod(u64 a, u64 b, u64 mod) {
  u64 y = u64(f80(a) * b / mod + 0.5);
  u64 r = a * b - y * mod;
  return i64(r) < 0 ? r + mod : r;
}