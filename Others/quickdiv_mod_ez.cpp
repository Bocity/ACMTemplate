#include <cstdio>
#include <iostream>

//计算 (1e8 + 6)!  (mod 1e8 + 7)  下快3倍   1.332/0.435s

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

/*
// 1 でも動作する
struct FastDiv {
  FastDiv() {}
  FastDiv(u64 n) : m(n) {
    s = (n == 1) ? 0 : 64 + std::__lg(n - 1);
    x = ((__uint128_t(1) << s) + n - 1) / n;
  }
  friend u64 operator / (u64 n, FastDiv d) { return __uint128_t(n) * d.x >> d.s; }
  friend u64 operator % (u64 n, FastDiv d) { return n - n / d * d.m; }
  u64 m, x; int s;
};
*/

// 1 は動作しない
struct FastDiv {
  FastDiv() {}
  FastDiv(u64 n) : m(n) {
    s = std::__lg(n - 1);
    x = ((__uint128_t(1) << (s + 64)) + n - 1) / n;
  }
  friend u64 operator / (u64 n, FastDiv d) { 
    return (__uint128_t(n) * d.x >> d.s) >> 64; 
  }
  friend u64 operator % (u64 n, FastDiv d) { return n - n / d * d.m; }
  u64 m, x; int s;
};

inline u64 mod64_32_small(u64 a, u32 b) {    //a 为 被取余  b为取余数
  u32 q, r;
  __asm__ (
    "divl\t%4"
    : "=a"(q), "=d"(r)
    : "0"(u32(a)), "1"(u32(a >> 32)), "rm"(b)
  );
  return r;
}
