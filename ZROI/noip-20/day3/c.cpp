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
#include <bitset>
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
const int N = 2005;
bitset<N> dp[N][N];
bitset<N> f[N], g[N], win[N];
char s[N][N];

void solve() {
  int n = rd();
  FOR(i, 1, n + 1) IO::rdstr(s[i] + 1);
  FOR(i, 1, n + 1) {
    FOR(j, 1, n + 1) win[i][j] = (s[i][j] == '1');
  }
  FOR(i, 1, n + 1) dp[i][i].set(i), f[i].set(i), g[i].set(i);
  for (int len = 2; len <= n; ++len) {
    for (int l = 1; l + len - 1 <= n; ++l) {
      int r = l + len - 1;
      // for (int i = l + 1; i <= r; ++i) {
      //   if (s[l][i] == '1' && dp[l + 1][r][i]) dp[l][r][l] = 1;
      // }
      bool b1 = (dp[l + 1][r] & win[l]).any();
      // for (int i = r - 1; i >= l; --i) {
      //   if (s[r][i] == '1' && dp[l][r - 1][i]) dp[l][r][r] = 1;
      // }
      bool b2 = (dp[l][r - 1] & win[r]).any();
      // for (int i = l + 1; i < r; ++i) {
      //   dp[l][r][i] = dp[l][i][i] && dp[i][r][i];
      // }
      dp[l][r] = f[l] & g[r];
      g[r][l] = dp[l][r][l] = b1;
      f[l][r] = dp[l][r][r] = b2;
    }
  }
  FOR(i, 1, n + 1) {
    if (dp[1][n][i]) cout << i << ' ';
  }
  cout << '\n';
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
