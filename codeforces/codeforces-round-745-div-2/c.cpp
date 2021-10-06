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
#define MULTI
const int N = 405;
char s[N][N];
int a[N][N], b[N][N], c[N][N], d[N][N];

void solve() {
  int n = rd(), m = rd();
  FOR(i, 0, n) IO::rdstr(s[i]);
  FOR(i, 0, n) {
    b[i][0] = a[i][0] = s[i][0] == '1';
    FOR(j, 1, m) b[i][j] = a[i][j] = ((s[i][j] == '1') + a[i][j - 1]);
  }
  FOR(j, 0, m) {
    a[0][j] = s[0][j] == '1';
    FOR(i, 1, n) c[i][j] = (s[i][j] == '1') + c[i - 1][j];
  }
  FOR(j, 0, m) {
    FOR(i, 1, n) a[i][j] += a[i - 1][j];
  }
  FOR(i, 0, n) {
    d[i][m] = m;
    ROF(j, 0, m) d[i][j] = (s[i][j] == '0') ? j : d[i][j + 1];
  } 
  int sum = 16;
  FOR(i, 0, n - 4) FOR(j, i + 4, n) FOR(k, 0, m - 3) {
    int _l = min(d[i][k + 1], d[j][k + 1]);
    chkmin(_l, m - 1);
    chkmax(_l, k + 3);
    FOR(l, _l, min(_l + 20, m)) {
    int cur = a[j-1][l-1] - a[j-1][k] - a[i][l-1] + a[i][k];
    cur += 2 * (j - i + l - k - 2);
    cur -= b[i][l-1] - b[i][k];
    cur -= b[j][l-1] - b[j][k];
    cur -= c[j-1][k] - c[i][k];
    cur -= c[j-1][l] - c[i][l];
    chkmin(sum, cur);
    }
  }
  cout << sum << '\n';
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
