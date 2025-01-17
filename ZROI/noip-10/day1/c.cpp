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
const int N = 105;
#define MULTI
i64 mod;

inline void reduce(i64 &x) {
  if (x >= mod) x -= mod;
}

i64 dp[2][N][N];
/* DP variables:
 * - current edge to be added O(n^2)
 * - times when SCCs were merged
 * - size of the only greatest SCC
 */

void solve() {
  int n = rd();
  mod = rd();
  memset(dp[0], 0, sizeof(dp[0]));
  dp[0][0][1] = 1;
  for (int i = 1; i <= n * (n - 1); ++i) {
    decltype(dp[0]) f = dp[~i & 1], g = dp[i & 1];
    memset(g, 0, sizeof(g));
    i64 ans = 0;
    for (int j = 0; j < n; ++j) {
      for (int k = 1; k <= n; ++k) {
        reduce(g[j][k + 1] += g[j][k]);
        if (f[j][k]) {
          if (n * (n - 1) / 2 + k * (k - 1) / 2 >= i) reduce(g[j][k] += f[j][k]); // fails form new SCC
          int lim = i - j - (!j) + (k == 1);
          // the state g[j][k] will need at least (k + j - 1) edges.
          // except for k == 1, (j - 1) edges.
          //        for j == 0, an extra edge.
          chkmin(lim, n);
          if (lim >= k + 1) { // form new SCC
            reduce(g[j + 1][k + 1] += f[j][k]);
            reduce(g[j + 1][lim + 1] += mod - f[j][k]);
          }
        }
        ans += g[j][k];
      }
    }
    cout << ans % mod << ' ';
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
