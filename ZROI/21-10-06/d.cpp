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
#include <cmath>
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
const int N = 305;
int n, m;
char s[N<<1];

inline int pop(u64 x, int l) { // count 1s in bit [0, l)
  x &= (1ull << l) - 1;
  return __builtin_popcountll(x);
}

u64 a[N];
namespace task1 {
void work() {
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j * m + i < n; ++j) {
      if (s[j * m + i] == '1') {
        a[i] |= 1ull << j;
      }
    }
  }
  int ans = 1e7;
  int l = ceil(1.0 * n / m);
  int lf = n % m;
  if (lf == 0) lf = m;
  for (int b = 0; b < (1 << l); ++b) {
    u64 msk = 0;
    for (int i = 0; i < l; ++i)
      if ((b >> i) & 1) msk ^= (1ull << (i + 1)) - 1;
    int cur = __builtin_popcountll(b);
    for (int i = 0; i < m; ++i) {
      int len = l;
      if (i >= lf) --len;
      int p = pop(a[i] ^ msk, len);
      cur += min(p, len - p);
    }
    chkmin(ans, cur);
  }
  cout << ans << '\n';
}
}

namespace task2 {
int c[N], sum[N];
int f[N][N], g[N][N]; // f <- min; g <- max
void work() {
  int ans = 1e7;
  int l = ceil(1.0 * n / m);
  int lf = n % m;
  if (lf == 0) lf = m;
  sum[0] = m;
  FOR(i, 1, l - 1) sum[i] = sum[i - 1] + m;
  sum[l - 1] = n;
  for (int b = 0; b < (1 << m); ++b) {
    for (int i = 0; i < l; ++i) c[i] = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j * m + i < n; ++j) {
        if ((s[j * m + i] - '0') != ((b >> i) & 1)) {
          ++c[j];
        }
      }
    }
    f[0][0] = g[0][0] = c[0];
    f[0][1] = g[0][1] = m - c[0];
    for (int i = 1; i < l; ++i) {
      for (int j = 0; j <= i + 1; ++j) {
        f[i][j] = 1e7;
        g[i][j] = -1;
        if (j != i + 1) { // do nothing
          chkmin(f[i][j], f[i - 1][j] + c[i]);
          chkmax(g[i][j], g[i - 1][j] + c[i]);
        }
        if (j != 0) { // rev
          chkmin(f[i][j], sum[i] - g[i - 1][j - 1] - c[i]);
          chkmax(g[i][j], sum[i] - f[i - 1][j - 1] - c[i]);
        }
      }
    }
    for (int i = 0; i <= l; ++i) {
      chkmin(ans, f[l - 1][i] + i);
    }
  }
  cout << ans << '\n';
}
}

void solve() {
  n = IO::rdstr(s) - s;
  m = rd();
  if (m > 15) task1::work();
  else task2::work();
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
