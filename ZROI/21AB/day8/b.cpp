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
#define MX 1000005
const i64 mod = 998244353;
int n;

i64 c[MX];
void ins(int x, i64 v) {
  while (x <= n) {
    c[x] = (c[x] + v) % mod;
    x += x & -x;
  }
}
i64 get(int x) {
  i64 ret = 0;
  while (x) {
    ret = (ret + c[x]) % mod;
    x -= x & -x;
  }
  return ret;
}

char s[MX];
struct qry {
  int l, r;
  bool operator<(const qry &b) const {
    return r < b.r;
  }
} q[25000000];
i64 dp[25000000];
int m;

namespace HASH {
i64 b = 114514;
i64 mod1 = 1000000007;
i64 p1[MX], p2[MX];
i64 h1[MX], rh1[MX];
void init() {
  p1[0] = 1;
  for (int i = 1; i < n; ++i) {
    p1[i] = p1[i - 1] * b % mod1;
  }
  h1[0] = s[0];
  for (int i = 1; i < n; ++i) {
    h1[i] = (h1[i - 1] * b + s[i]) % mod1;
  }
  rh1[n - 1] = s[n - 1];
  for (int i = n - 2; i >= 0; --i) {
    rh1[i] = (rh1[i + 1] * b + s[i]) % mod1;
  }
}
inline i64 g1(int l, int r) {
  if (!l) return h1[r];
  return (h1[r] - h1[l - 1] * p1[r - l + 1] % mod1 + mod1) % mod1;
}
inline i64 rg1(int l, int r) {
  if (r == n - 1) return rh1[l];
  return (rh1[l] - rh1[r + 1] * p1[r - l + 1] % mod1 + mod1) % mod1;
}
}

inline void getall() {
  HASH::init();
  for (int i = 1; i <= n; ++i) q[m].l = q[m].r = i, ++m;
  for (int l = 1; l < n; ++l) {
    for (int r = l + 1; r <= n; ++r) {
      int m1 = l + (r - l) / 2;
      int m2 = m1 + ((l + r) & 1);
      if (HASH::g1(l - 1, m1 - 1) == HASH::rg1(m2 - 1, r - 1)) {
            q[m].l = l, q[m].r = r;
            ++m;
          }
    }
  }
  sort(q, q + m);
  for (int i = 0; i < m; ++i) dp[i] = 1;
}

void solve() {
  n = IO::rdstr(s) - s;
  getall();
  int lt = 0, rt = 0;
  for (int r = 1; r <= n; ++r) {
    lt = rt;
    while (rt < m && q[rt].r == r) ++rt;
    if (rt == lt) continue;
    for (int i = lt; i < rt; ++i) {
      dp[i] = (dp[i] + get(r) - get(q[i].l) + mod) % mod;
    }
    for (int i = lt; i < rt; ++i) {
      ins(q[i].l, dp[i]);
    }
  }
  i64 ans = 0;
  for (int i = 0; i < m; ++i) {
    ans += dp[i];
  }
  cout << ans % mod << '\n';
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
