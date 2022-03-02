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
char in[1 << 24]; // sizeof in varied in problem
char const *o;
void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0; // set 0 at the end of buffer.
}
int rd() {
  unsigned u = 0, s = 0;
  while (*o && *o <= 32)
    ++o; // skip whitespaces...
  if (*o == '-')
    s = ~s, ++o;
  else if (*o == '+')
    ++o; // skip sign
  while (*o >= '0' && *o <= '9')
    u = (u << 3) + (u << 1) + (*o++ - '0'); // u * 10 = u * 8 + u * 2 :)
  return static_cast<int>((u ^ s) + !!s);
}
char *rdstr(char *s) {
  while (*o && *o <= 32)
    ++o;
  while (*o > 32)
    *s++ = *o++;
  return s;
}
} // namespace IO

/********************************* utility ************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef pair<int, int> pii;
#define pb(x) push_back(x)
#define mkp(x, y) make_pair(x, y)
#define fi first
#define se second
#define FOR(x, y, z) for (int x = y; x < z; ++x) // always [y, z)
#define ROF(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T> void chkmax(T &a, const T &b) { a = max(a, b); }
template <typename T> void chkmin(T &a, const T &b) { a = min(a, b); }
pii operator+(const pii &a, const pii &b) {
  return mkp(a.fi + b.fi, a.se + b.se);
}
// clang-format off
// clang-format on

/*********************************** solution *********************************/
using IO::rd;
const int N = 505;
const i64 mod = 998244353;
i64 f[N][N], g[N][N];
bool E[N][N];
i64 fac[N << 1], ifac[N << 1], inv[N << 1];

void work() {
  fac[0] = fac[1] = ifac[0] = ifac[1] = inv[1] = 1ll;
  for (int i = 2; i < N << 1; ++i) {
    inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    fac[i] = fac[i - 1] * i % mod;
    ifac[i] = ifac[i - 1] * inv[i] % mod;
  }
}

inline i64 C(int n, int k) {
  if (k > n || k < 0) return 0;
  return fac[n] * ifac[k] % mod * ifac[n - k] % mod;
}

void solve() {
  int n = rd(), m = rd();
  FOR(i, 0, m) {
    int u = rd(), v = rd();
    E[u][v] = E[v][u] = 1;
  }
  FOR(i, 1, 2 * n) {
    if (E[i][i + 1]) {
      f[i][i + 1] = g[i][i + 1] = 1;
    }
  }
  for (int len = 4; len <= n * 2; len += 2) {
    for (int l = 1; l + len - 1 <= n * 2; ++l) {
      int r = l + len - 1;
      if (E[l][r]) g[l][r] = f[l + 1][r - 1];
      for (int mid = l + 1; mid < r; mid += 2) {
        f[l][r] = (f[l][r] + g[l][mid] * f[mid + 1][r] % mod * C(len / 2, (r - mid) / 2) % mod) % mod;
      }
      f[l][r] += g[l][r];
      f[l][r] %= mod;
    }
  }
  cout << f[1][n * 2] << '\n';
}

int main() {
  work();
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--)
    solve();
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
