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
const int N = 2e3+5;
const int p = 1e9+7;
inline void red(int &x) { if (x >= p) x -= p; }

int dp[N][N];
int inv[N*N], fac[N*N], ifac[N*N];

inline int C(int n, int k) {
  if (k < 0 || k > n) return 0;
  return 1ll * fac[n] * ifac[k] % p * ifac[n - k] % p;
}

void solve() {
  int n = rd(), k = rd();
  if (k == 1) {
    puts("1");
    return;
  }
  inv[1] = fac[1] = ifac[1] = ifac[0] = fac[0] = 1;
  for (int i = 2; i < N * N; ++i) {
    fac[i] = 1ll * fac[i - 1] * i % p;
    inv[i] = 1ll * p / i * (p - inv[p % i]) % p;
    ifac[i] = 1ll * ifac[i - 1] * inv[i] % p;
  }
  FOR(i, 1, n + 1) dp[i][0] = 1;
  FOR(i, 1, n + 1) FOR(j, 1, i + 1) {
    if (j < i) dp[i][j] = dp[i - 1][j];
    red(dp[i][j] += 1ll * dp[i][j - 1] * C(n * k - i - j - (k - 2) * (j - 1), k - 2) % p);
  }
  cout << 1ll * dp[n][n] * fac[n] % p << '\n';
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
