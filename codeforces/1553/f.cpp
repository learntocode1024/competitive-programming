/*******************************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: $%M%$ $%D%$, $%Y%$
 * Algorithm:
 * Difficulty:
 *
 ******************************************************************************/
#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/********************************* macros *************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
#define pb(x) push_back(x)
#define fi first
#define se second
#define REP(x, y, z) for (int x = y; x < z; ++x) // always [y, z)
#define PER(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T> void chkmax(T &a, const T &b) { a = max(a, b); }
template <typename T> void chkmin(T &a, const T &b) { a = min(a, b); }

/*********************************** solution *********************************/
#define MX 300050
i64 a[MX];
i64 n, mxa = 300005;

i64 c[MX], d[MX];
i64 get(i64 *c, i64 x) {
  i64 ret = 0;
  while (x) {
    ret += c[x];
    x -= x & -x;
  }
  return ret;
}

void ins(i64 *c, int x, i64 v) {
  while (x <= mxa) {
    c[x] += v;
    x += x & -x;
  }
}

i64 f[MX];

void solve() {
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    chkmax(mxa, a[i]);
  }
  i64 pre = 0, pmx = 0;
  for (i64 i = 1; i <= n; ++i) {
    f[i] = f[i - 1];
    f[i] += (i - 1) * a[i] + pre;
    f[i] -= get(c, a[i]);
    for (int j = 1; j <= pmx / a[i]; ++j) {
      f[i] -= j * a[i] * (get(d, min(mxa, (j + 1) * a[i] - 1)) - get(d, min(mxa, j * a[i] - 1)));
    }
    for (int j = a[i]; j <= mxa; j += a[i])
      ins(c, j, a[i]);
    pre += a[i];
    ins(d, a[i], 1);
    chkmax(pmx, a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    cout << f[i] << '\n';
  }
}

int main() {
#ifndef MASSIVE_INPUT
  // IO::init_in();
#endif
#ifdef MULTI
  int T = IO::read();
  while (T--)
    solve(), T &&clear();
#else
  solve();
#endif
  return 0;
}
