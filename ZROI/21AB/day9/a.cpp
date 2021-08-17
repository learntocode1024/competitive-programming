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
#define MX 505
int n, a[MX];
i64 mod = 998244353;
int f = 1;

i64 Q_pow(i64 a, int x) {
  i64 ret = 1;
  while (x) {
    if (x & 1) ret = ret * a % mod;
    a = a * a % mod;
    x >>= 1;
  }
  return ret;
}

namespace sub2 {
i64 dp[1 << 20];
void solve() {
  dp[0] = 1;
  for (int i = 1; i < (1 << n); ++i) {
    int tot = 0;
    static int p[25];
    for (int j = 0; j < n; ++j) {
      if (i & (1 << j)) {
        p[tot++] = j;
      }
    }
    bool f = 1;
    for (int j = 1; j < tot; ++j) {
      if (a[p[j - 1]] == a[p[j]]) {
        f = 0;
        break;
      }
    }
    if (!f) continue;
    dp[i] = dp[i - (1 << p[0])];
    if (tot > 1) dp[i] += dp[i - (1 << p[tot - 1])];
    for (int j = 1; j < tot - 1; ++j) {
      dp[i] += dp[i - (1 << p[j])];
    }
    dp[i] %= mod;
  }
  cout << dp[(1 << n) - 1] * f % mod << '\n';
}
}

namespace sub3 {
int c[4];
i64 dp[MX][MX][MX];
void solve() {
  cout << f * Q_pow(2, n - 1) % mod << '\n';
}
}

void solve() {
  n = rd();
  int cnt = 0, pos, ma = 0;
  for (int i = 0; i < n; ++i) {
    a[i] = rd();
    chkmax(ma, a[i]);
    if (i > 0 && a[i - 1] == a[i]) ++cnt, pos = i;
  }
  if (cnt > 1) {
    puts("0");
    return;
  }
  if (cnt == 1) {
    for (int i = pos; i < n; ++i) {
      a[i] = a[i + 1];
    }
    --n;
    f = 2;
  }
  if (n <= 20) {
    sub2::solve();
  } else {
    if (ma == 2) sub3::solve();
  }
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

