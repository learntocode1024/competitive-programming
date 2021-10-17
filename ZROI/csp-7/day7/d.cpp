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

/*********************************** solution *********************************/
using IO::rd;
// #define MULTI
const int N = 105;
const int S = 15;
const int p = 998244353;
int fac[N] = {1, 1}, ifac[N] = {1, 1}, inv[N] = {0, 1};
int a[N][S];
int maxa[S];
char str[N];
int n, m;
int ans = 0;

inline int C(int n, int m) {
  if (m < 0 || m > n) return 0;
  return 1ll * fac[n] * ifac[m] % p * ifac[n - m] % p;
}
inline int iC(int n, int m) {
  if (m < 0 || m > n) return 0;
  return 1ll * ifac[n] * fac[m] % p * fac[n - m] % p;
}

namespace sub3 {
int pr[N][N];
inline void work() {
  for (int i = 0; i <= m; ++i) {
    for (int j = 0; i + j <= m; ++j) {
      pr[i][j] = 0;
      for (int k = 0; k < n; ++k) {
        if (a[k][0] < i || a[k][1] < j) continue;
        int cur = 1ll * C(m - i - j, a[k][0] - i) * iC(m, a[k][0]) % p;
        pr[i][j] = (pr[i][j] + 1ll * (p + 1 - pr[i][j]) * cur) % p;
      }
      ans = (ans + 1ll * pr[i][j] * C(i + j, i)) % p;
    }
  }
}
}

namespace sub1 {
inline void work() {
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      int p = 0;
      for (int k = 0; k < n; ++i) {
        
      }
    }
  }
}
}

namespace bf {
int c[S];

inline int mul(int *c, int *d) {
  int ret = fac[c[10] - d[10]];
  for (int i = 0; i < 10; ++i) {
    if (c[i] < d[i]) return 0;
    ret = 1ll * ret * ifac[c[i] - d[i]] % p;
  }
  return ret;
}

inline int imul(int *c) {
  int ret = ifac[c[10]];
  for (int i = 0; i < 10; ++i) {
    ret = 1ll * ret * fac[c[i]] % p;
  }
  return ret;
}

inline int mul(int *c) {
  int ret = fac[c[10]];
  for (int i = 0; i < 10; ++i) {
    ret = 1ll * ret * ifac[c[i]] % p;
  }
  return ret;
}

inline void calc() {
  int dp = 0;
  for (int i = 0; i < n; ++i) {
    int pr = 1ll * mul(a[i], c) * imul(a[i]) % p;
    dp = (dp + 1ll * (p + 1 - dp) * pr) % p;
  }
  ans = (ans + 1ll * mul(c) * dp) % p;
}

void dfs(int sum, int i) {
  if (i == 10) {
    c[10] = m - sum;
    calc();
    return;
  }
  for (int k = 0; k <= min(sum, maxa[i]); ++k) {
    c[i] = k;
    dfs(sum - k, i + 1);
  }
  c[i] = 0;
}

inline void work() {
  dfs(m, 0);
}
}

void solve() {
  n = rd(), m = rd();
  bool s2 = 1;
  FOR(i, 0, n) {
    IO::rdstr(str);
    FOR(j, 0, m) {
      ++a[i][str[j] - '0'];
      if (str[j] != '0' && str[j] != '1') s2 = 0;
      chkmax(maxa[str[j] - '0'], a[i][str[j] - '0']);
    }
    a[i][10] = m;
  }
  if (s2) sub3::work();
  else bf::work();
  cout << ans << '\n';
}

int main() {
  FOR(i, 2, N) {
    inv[i] = 1ll * (p - p / i) * inv[p % i] % p;
    fac[i] = 1ll * fac[i - 1] * i % p;
    ifac[i] = 1ll * ifac[i - 1] * inv[i] % p;
  }
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
