// (1e8)! mod (1e18 + 3) 下快7倍
// 2.723 s / 0.392 s
//商在2^64以上时将会产生负点误差   模数要求奇数
using i64 = long long;
using u64 = unsigned long long;
using u128 = __uint128_t;

struct Mod64 {
  Mod64() : n_(0) {}
  Mod64(u64 n) : n_(init(n)) {}
  static u64 modulus() { return mod; }
  static u64 init(u64 w) { return reduce(u128(w) * r2); }
  static void set_mod(u64 m) {
    mod = m; assert(mod & 1);
    inv = m; for (int i = 0; i < 5; ++i) inv *= 2 - inv * m;
    r2 = -u128(m) % m;
  }
  static u64 reduce(u128 x) {
    u64 y = u64(x >> 64) - u64((u128(u64(x) * inv) * mod) >> 64);
    return i64(y) < 0 ? y + mod : y;
  }
  Mod64& operator += (Mod64 rhs) { n_ += rhs.n_ - mod; if (i64(n_) < 0) n_ += mod; return *this; }
  Mod64 operator + (Mod64 rhs) const { return Mod64(*this) += rhs; }
  Mod64& operator *= (Mod64 rhs) { n_ = reduce(u128(n_) * rhs.n_); return *this; }
  Mod64 operator * (Mod64 rhs) const { return Mod64(*this) *= rhs; }
  u64 get() const { return reduce(n_); }
  static u64 mod, inv, r2;
  u64 n_;
};
u64 Mod64::mod, Mod64::inv, Mod64::r2;

inline u64 mod128_64_small(u128 a, u64 b) {
  u64 q, r;
  __asm__ (
    "divq\t%4"
    : "=a"(q), "=d"(r)
    : "0"(u64(a)), "1"(u64(a >> 64)), "rm"(b)
  );
  return r;
}

u64 fact_mod_fast(int N, u64 mod) {
  Mod64::set_mod(mod);
  Mod64 ret = Mod64(1), one = ret, t = one;
  for (int i = 1; i <= N; ++i) {
    ret *= t;
    t += one;
  }
  return ret.get();
}
