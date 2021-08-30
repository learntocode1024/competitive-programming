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
  unsigned long long u = 0, s = 0;
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
const int N = 100005;
int a[N], s[N];
int n;
#define MULTI
bool dp[2][1005][1005];

void solve() {
  n = rd();
  for (int i = 0; i < n; ++i) a[i] = rd();
  int xsum = 0;
  for (int i = 0; i < n; ++i) xsum ^= a[i];
  if (!xsum) {
    cout << "Draw\n";
    return;
  }
  int t = 31 - __builtin_clz(xsum);
  for (int i = 0; i < n; ++i) a[i] = (a[i] >> t) & 1;
  s[0] = a[0];
  for (int i = 1; i < n; ++i) s[i] = s[i - 1] ^ a[i];
  for (int i = 0; i < n; ++i) for (int j = i; j < n; ++j) dp[0][i][j] = dp[1][i][j] = 0;
  for (int i = 0; i < n; ++i) dp[a[i]][i][i] = 1;
  for (int len = 2; len <= n; ++len) {
    for (int l = 0; l + len <= n; ++l) {
      int r = l + len - 1;
      int S = s[r];
      if (l) S ^= s[l - 1];
      dp[1][l][r] |= !dp[S][l][r - 1];
      dp[1][l][r] |= !dp[S][l + 1][r];
      dp[0][l][r] |= !dp[S ^ 1][l][r - 1];
      dp[0][l][r] |= !dp[S ^ 1][l + 1][r];
    }
  }
  if (dp[1][0][n - 1]) cout << "Alice\n";
  else cout << "Bob\n";
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
