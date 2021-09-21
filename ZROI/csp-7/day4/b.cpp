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
const int N = 1005;
char s[N][N];
int a[N][N], b[N][N];
int n, m, ex, ey;
int ne1[N], ne2[N];

void solve() {
  n = rd(), m = rd();
  FOR(i, 0, n) IO::rdstr(s[i]);
  FOR(i, 0, n) FOR(j, 0, m) if (s[i][j] == '1') ne1[i] = 1, ne2[j] = 1;
  FOR(i, 0, n) ex += 1 - ne1[i];
  FOR(j, 0, m) ey += 1 - ne2[j];
  int ans = 0;
  FOR(i, 0, n) FOR(j, 0, m) if (s[i][j] == '0') ans += 3;
  FOR(j, 0, m) if (s[0][j] == '0') a[0][j] = 1;
  FOR(i, 1, n) {
    FOR(j, 0, m) a[i][j] = a[i - 1][j];
    FOR(j, 0, m) if (s[i][j] == '0') ++a[i][j];
    int mn = 1e8;
    FOR(j, 0, m) chkmin(mn, a[i][j]);
    FOR(j, 0, m) chkmin(a[i][j], mn + (s[i][j] == '0'));
  }
  int mn = 1e8;
  FOR(i, 0, m) chkmin(mn, a[n - 1][i]);
  int ret = ans + mn + ey;
  FOR(i, 0, n) if (s[i][0] == '0') b[i][0] = 1;
  FOR(j, 1, m) {
    FOR(i, 0, n) b[i][j] = b[i][j - 1];
    FOR(i, 0, n) if (s[i][j] == '0') ++b[i][j];
    int mn = 1e8;
    FOR(i, 0, n) chkmin(mn, b[i][j]);
    FOR(i, 0, n)
      chkmin(b[i][j], mn + (s[i][j] == '0'));
  }
  mn = 1e8;
  FOR(i, 0, n) chkmin(mn, b[i][m - 1]);
  chkmin(ret, ans + mn + ex);
  cout << ret << '\n';
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
