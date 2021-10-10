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
const int N = 405;
const int p = 1e9+7;
int fac[N];
inline void red(int &x) { if (x >= p) x -= p; }
int q_pow(int x, int a) {
  int ret = 1;
  while (a) {
    if (a & 1) ret = 1ll * ret * x % p;
    x = 1ll * x * x % p;
    a >>= 1;
  }
  return ret;
}
int a[N], b[N];
int n, k;

namespace sub1 {
int c[N];
int d[N];
void work() {
  FOR(i, 1, n + 1) c[i] = i;
  int ans = 0;
  do {
    FOR(i, 1, n + 1) d[i] = a[i] + b[c[i]];
    sort(d + 1, d + n + 1);
    red(ans += d[n - k + 1]);
  } while (next_permutation(c + 1, c + n + 1));
  cout << 1ll * ans * q_pow(fac[n], p - 2) % p << '\n';
}
}

namespace sub23 {
inline int calc(int x, int y) {
  int mx = a[x] + b[y];
  int cnt = 1;
  int l = 0;
  int tot = 0;
  for (int i = n; i > x; --i) {
    while (l + 1 < y && b[l + 1] + a[i] < mx) ++l;
    int c = l - tot;
    ++tot;
    if (c <= 0) cnt = 0;
    else cnt = 1ll * cnt * c % p;
  }
  l = 0;
  tot = 0;
  for (int i = n; i > y; --i) {
    while (l + 1 < x && b[i] + a[l + 1] <= mx) ++l;
    int c = l - tot;
    ++tot;
    if (c <= 0) cnt = 0;
    else cnt = 1ll * cnt * c % p;
  }
  cnt = 1ll * cnt * fac[x + y - n - 1] % p;
  /* mx = 1; */
  return 1ll * cnt * mx % p;
}
void work() {
  int ans = 0;
  for (int i = n; i; --i) {
    for (int j = n; j > n - i && n - j < i; --j) {
      red(ans += calc(i, j));
    }
  }
  cout << 1ll * ans * q_pow(fac[n], p - 2) % p << '\n';
}
}

namespace sub45 {
int dp[1<<14][14][14];
int c[N], d[N];
inline int calc(int x, int y) {
  int mx = a[x] + b[y];
  dp[0][0][0] = 1;
  int tot = 0;
  FOR(i, 1, n + 1) if (i != x) c[tot++] = a[i];
  tot = 0;
  FOR(j, 1, n + 1) if (j != y) d[tot++] = b[j];
  for (int u = 1; u < (1 << (n - 1)); ++u) {
    int i = __builtin_popcount(u) - 1;
    for (int k = 0; k <= i + 1; ++k) {
      for (int l = 0; k + l <= i + 1; ++l) {
        dp[u][k][l] = 0;
      }
    }
    for (int j = 0; j < n - 1; ++j) {
      if ((u >> j) & 1) {
        int v = u - (1 << j);
        if (c[i] + d[j] < mx) for (int k = 0; k <= i + 1; ++k) {
          for (int l = 0; k + l <= i + 1; ++l) {
            red(dp[u][k][l] += dp[v][k][l]);
          }
        }
        if (i <= x - 2 && c[i] + d[j] == mx) for (int k = 0; k <= i + 1; ++k) {
          for (int l = 0; k + l <= i + 1; ++l) {
            red(dp[u][k][l] += dp[v][k][l - 1]);
          }
        }
        if (c[i] + d[j] > mx) for (int k = 0; k <= i + 1; ++k) {
          for (int l = 0; k + l <= i + 1; ++l) {
            red(dp[u][k][l] += dp[v][k - 1][l]);
          }
        }
      }
    }
  }
  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i < k && i + j + 1 >= k) red(cnt += dp[(1 << (n - 1)) - 1][i][j]);
    }
  }
  return 1ll * cnt * mx % p;
}
void work() {
  int ans = 0;
  for (int i = n; i; --i) {
    for (int j = n; j; --j) {
      red(ans += calc(i, j));
    }
  }
  cout << 1ll * ans * q_pow(fac[n], p - 2) % p << '\n';
}
}
void solve() {
  n = rd(), k = rd();
  FOR(i, 1, n + 1) a[i] = rd();
  FOR(i, 1, n + 1) b[i] = rd();
  sort(a + 1, a + n + 1);
  sort(b + 1, b + n + 1);
  fac[0] = fac[1] = 1;
  FOR(i, 1, n + 1) fac[i] = 1ll *  fac[i - 1] * i % p;
  if (n <= 10) sub1::work();
  else if (k == 1) sub23::work();
  else if (n <= 15) sub45::work();
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
