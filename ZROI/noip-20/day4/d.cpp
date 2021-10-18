/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date:
 * Algorithm:
 * Difficulty:
 *
 *********************************************************************/

#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/********************************** buffer IO *********************************/
namespace IO {
char in[1 << 24];  // sizeof in varied in problem
char const *o;
void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0;  // set 0 at the end of buffer.
}
int rd() {
  unsigned u = 0, s = 0;
  while (*o && *o <= 32) ++o;  // skip whitespaces...
  if (*o == '-')
    s = ~s, ++o;
  else if (*o == '+')
    ++o;  // skip sign
  while (*o >= '0' && *o <= '9')
    u = (u << 3) + (u << 1) + (*o++ - '0');  // u * 10 = u * 8 + u * 2 :)
  return static_cast<int>((u ^ s) + !!s);
}
char *rdstr(char *s) {
  while (*o && *o <= 32) ++o;
  while (*o > 32) *s++ = *o++;
  *s = '\0';
  return s;
}
}  // namespace IO

/********************************* utility ************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef pair<int, int> pii;
#define pb(x) push_back(x)
#define mkp(x, y) make_pair(x, y)
#define fi first
#define se second
#define FOR(x, y, z) for (int x = y; x < z; ++x)  // always [y, z)
#define ROF(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T>
void chkmax(T &a, const T &b) {
  a = max(a, b);
}
template <typename T>
void chkmin(T &a, const T &b) {
  a = min(a, b);
}
pii operator+(const pii &a, const pii &b) {
  return mkp(a.fi + b.fi, a.se + b.se);
}
// require c++14 to compile
#include <cassert>
#include <cstdint>
#include <iostream>
using namespace std;

template <uint32_t mod>
struct MontgomeryModInt {
  using mint = MontgomeryModInt;
  using i32 = int32_t;
  using u32 = uint32_t;
  using u64 = uint64_t;

  static constexpr u32 get_r() {
    u32 ret = mod;
    for (i32 i = 0; i < 4; ++i) ret *= 2 - mod * ret;
    return ret;
  }

  static constexpr u32 r = get_r();
  static constexpr u32 n2 = -u64(mod) % mod;
  static_assert(r * mod == 1, "invalid, r * mod != 1");
  static_assert(mod < (1 << 30), "invalid, mod >= 2 ^ 30");
  static_assert((mod & 1) == 1, "invalid, mod % 2 == 0");

  u32 a;

  constexpr MontgomeryModInt() : a(0) {}
  constexpr MontgomeryModInt(const int64_t &b)
      : a(reduce(u64(b % mod + mod) * n2)){};

  static constexpr u32 reduce(const u64 &b) {
    return (b + u64(u32(b) * u32(-r)) * mod) >> 32;
  }

  constexpr mint &operator+=(const mint &b) {
    if (i32(a += b.a - 2 * mod) < 0) a += 2 * mod;
    return *this;
  }

  constexpr mint &operator-=(const mint &b) {
    if (i32(a -= b.a) < 0) a += 2 * mod;
    return *this;
  }

  constexpr mint &operator*=(const mint &b) {
    a = reduce(u64(a) * b.a);
    return *this;
  }

  constexpr mint &operator/=(const mint &b) {
    *this *= b.inverse();
    return *this;
  }

  constexpr mint operator+(const mint &b) const { return mint(*this) += b; }
  constexpr mint operator-(const mint &b) const { return mint(*this) -= b; }
  constexpr mint operator*(const mint &b) const { return mint(*this) *= b; }
  constexpr mint operator/(const mint &b) const { return mint(*this) /= b; }
  constexpr bool operator==(const mint &b) const {
    return (a >= mod ? a - mod : a) == (b.a >= mod ? b.a - mod : b.a);
  }
  constexpr bool operator!=(const mint &b) const {
    return (a >= mod ? a - mod : a) != (b.a >= mod ? b.a - mod : b.a);
  }
  constexpr mint operator-() const { return mint() - mint(*this); }

  constexpr mint pow(u64 n) const {
    mint ret(1), mul(*this);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }
  
  constexpr mint inverse() const { return pow(mod - 2); }

  friend ostream &operator<<(ostream &os, const mint &b) {
    return os << b.get();
  }

  friend istream &operator>>(istream &is, mint &b) {
    int64_t t;
    is >> t;
    b = MontgomeryModInt<mod>(t);
    return (is);
  }
  
  constexpr u32 get() const {
    u32 ret = reduce(a);
    return ret >= mod ? ret - mod : ret;
  }

  static constexpr u32 get_mod() { return mod; }
};

/*********************************** solution *********************************/
using IO::rd;
// #define MULTI
typedef  MontgomeryModInt<1000000007> mint;
const int N = 18;
const int p = 1e9+7;
bool g[N][N];
int n, m;
mint pw[N * N];
mint f[1 << N];
char g00[1 << (N/2)][1 << (N/2)], g01[1 << (N/2)][1 << (N/2)], g10[1 << (N/2)][1 << (N/2)], g11[1 << (N/2)][1 << (N/2)];
int h, w;

inline void red(int &x) { if (x >= p) x -= p; }

inline int ways(int s, int t) {
  int s1 = s & w, s2 = s >> h, t1 = t & w, t2 = t >> h;
  return (int)g00[s1][t1] + g01[s1][t2] + g10[s2][t1] + g11[s2][t2];
}

inline void prework() {
  for (int s = 1; s < 1 << h; ++s) {
    for (int t = 1; t < 1 << h; ++t) {
      if (s & t) continue;
      for (int i = 0; i < h; ++i) {
        for (int j = 0; j < h; ++j) {
          if (((s >> i) & 1) && ((t >> j) & 1) && g[i][j]) ++g00[s][t];
        }
      }
    }
  }
  for (int s = 1; s < 1 << h; ++s) {
    for (int t = 1; t < 1 << (n - h); ++t) {
      for (int i = 0; i < h; ++i) {
        for (int j = 0; j < n - h; ++j) {
          if (((s >> i) & 1) && ((t >> j) & 1) && g[i][j + h]) ++g01[s][t];
        }
      }
    }
  }
  for (int s = 1; s < 1 << (n - h); ++s) {
    for (int t = 1; t < 1 << h; ++t) {
      for (int i = 0; i < n - h; ++i) {
        for (int j = 0; j < h; ++j) {
          if (((s >> i) & 1) && ((t >> j) & 1) && g[i + h][j]) ++g10[s][t];
        }
      }
    }
  }
  for (int s = 1; s < 1 << (n - h); ++s) {
    for (int t = 1; t < 1 << (n - h); ++t) {
      if (s & t) continue;
      for (int i = 0; i < n - h; ++i) {
        for (int j = 0; j < n - h; ++j) {
          if (((s >> i) & 1) && ((t >> j) & 1) && g[i + h][j + h]) ++g11[s][t];
        }
      }
    }
  }
}

void solve() {
  n = rd(), m = rd();
  h = n / 2;
  w = (1 << h) - 1;
  for (int i = 0; i < m; ++i) {
    int a = rd() - 1, b = rd() - 1;
    g[a][b] = 1;
  }
  prework();
  pw[0] = 1;
  f[0] = 1;
  FOR(i, 1, m + 1) {
    pw[i] = pw[i - 1] * 2;
  }
  for (int u = 1; u < (1 << n); ++u) {
    for (int v = u; v; v = (v - 1) & u) {
      mint cur = pw[ways(v, u ^ v)] * f[u ^ v];
      if (__builtin_parity(v)) {
        f[u] += cur;
      } else {
        f[u] -= cur;
      }
    }
  }
  cout << pw[m] - f[(1 << n) - 1] << '\n';
}

int main() {
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--) solve();
#else
  solve();
#endif
  return 0;
}
/*
 * checklist:
 * - IO buffer size
 * - potential out-of-bound Errors
 * - inappropriate variable type
 * - potential Arithmetic Error
 * - potential Arithmetic Overflow
 * - typo / logical flaws
 * - clean-up on multiple test cases
 * - sufficient stress tests / random data tests
*/
