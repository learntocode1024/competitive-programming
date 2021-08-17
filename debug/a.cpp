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
#include <iomanip>
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
typedef long double f80;
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
const int N = 14, M = 105;
int u[M], v[M];
int n, m;
f80 p;
f80 f[1 << N];

void solve() {
  cin >> n >> m >> p;
  p /= 100.0l;
  FOR(i, 0, m) cin >> u[i] >> v[i], --u[i], --v[i];
  for (int i = 1; i < 1 << n; ++i) {
    f[i] = 1.0l;
    int x = __builtin_ffs(i) - 1;
    for (int j = (i - 1) & i; j >= (1 << x); j = (j - 1) & i) {
      if (!(j & (1 << x))) continue;
      f80 cur(1);
      for (int k = 0; k < m; ++k) {
        if (!(i & (1 << u[k]))) continue;
        if (!(i & (1 << v[k]))) continue;
        if (!(((j & (1 << u[k])) != 0) ^ ((j & (1 << v[k])) != 0))) continue;
        cur *= p;
      }
      f[i] -= cur * f[j];
    }
  }
  cout << fixed << setprecision(14) << f[(1 << n) - 1] << '\n';
}

int main() {
  // IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--) solve();
#else
  solve();
#endif
  return 0;
}

