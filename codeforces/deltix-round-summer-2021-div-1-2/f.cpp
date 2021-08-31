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

/*********************************** solution *********************************/
using IO::rd;
const int N = 14, S = 1 << N;

int a[N];
int n;
const i64 mod = 1e9 + 7;
i64 b[N][N];
i64 h[N][S], pr[S];

inline void reduce(i64 &x) {
  if (x >= mod) x -= mod;
}

inline i64 g(int s, int t) {
  i64 ret = 1;
  FOR(i, 0, n) {
    if (s & (1 << i)) ret = ret * h[i][t] % mod;
  }
  return ret;
}

int Q_pow(i64 x, int y) {
  i64 ret = 1;
  while (y) {
    if (y & 1)
      ret = ret * x % mod;
    x = x * x % mod;
    y >>= 1;
  }
  return ret;
}

inline int inv(int x) { return Q_pow(x, mod - 2); }

void solve() {
  n = rd();
  int m = 1 << n;
  FOR(i, 0, n) a[i] = rd();
  FOR(i, 0, n) FOR(j, 0, i) {
    i64 x = inv(a[i] + a[j]);
    b[i][j] = a[i] * x % mod;
    b[j][i] = a[j] * x % mod;
  }
  FOR(i, 0, n) FOR(j, 0, m) {
    h[i][j] = 1;
    FOR(k, 0, n) {
      if (k != i && j & (1 << k))
        h[i][j] = h[i][j] * b[i][k] % mod;
    }
  }
  int mask = m - 1;
  FOR(i, 1, m) {
    pr[i] = 1;
    for (int j = (i - 1) & i; j; j = (j - 1) & i) {
      reduce(pr[i] += mod - (g(j, i ^ j) * pr[j] % mod));
    }
  }
  i64 ans = 0;
  FOR(i, 1, m) {
    ans += pr[i] * g(i, mask ^ i) % mod * __builtin_popcount(i) % mod;
  }
  cout << ans % mod << '\n';
}

int main() {
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
