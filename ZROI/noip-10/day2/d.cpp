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
int n;
i64 p;
const int N = 3005, N2 = (N * N) << 1;
i64 fac[N2], ifac[N2], inv[N2];

inline void red(i64 &x) {
  if (x >= p) x -= p;
}

void init() {
  fac[0] = ifac[0] = fac[1] = ifac[1] = inv[1] = 1;
  FOR(i, 2, n * n * 2 + 10) {
    inv[i] = inv[p % i] * (p - p / i) % p;
    fac[i] = fac[i - 1] * i % p;
    ifac[i] = ifac[i - 1] * inv[i] % p;
  }
}

inline i64 C(int n, int k) {
  if (k < 0 || k > n) return 0ll;
  return fac[n] * ifac[n - k] % p * ifac[k] % p;
}

i64 f[N][N], g[N][N];

void solve() {
  n = rd();
  p = rd();
  init();
  FOR(i, 0, n + 1) g[0][i] = 1;
  FOR(i, 1, n + 1) FOR(j, i, n + 1) red(g[i][j] = g[i - 1][j] + g[i][j - 1]);
  f[1][0] = 1;
  FOR(i, 1, n + 1) FOR(j, 0, i + 1) {
    red(f[i + 1][j] += f[i][j]);
    if (i == j) continue;
    int res = n * n * 2 - i - j - 1 - j * n * 2;
    if (i > j + 1) {
      f[i][j + 1] = (f[i][j + 1] + f[i][j] * C(res, 2 * n) % p * g[n][n]) % p;
    } else {
      for (int k = 0; k <= n; ++k) {
        f[i][j + 1] = (f[i][j + 1] + f[i][j] * g[n - k][n] % p * C(res - k - 1, 2 * n - k)) % p;
      }
    }
  }
  cout << f[n][n - 1] << '\n';
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
