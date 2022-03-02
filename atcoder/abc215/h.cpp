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

#include "utils"
#include "io"
#include "modint"
using mint = MontgomeryModInt<998244353>;

int f[1 << 20], g[1 << 20];
int flag[1 << 20];
const int N = 2000001;
mint h[1 << 20];
mint inv[N], fac[N], ifac[N];

void init() {
  fac[0] = fac[1] = ifac[0] = ifac[1] = inv[1] = 1;
  for (int i = 2; i < N; ++i) {
    fac[i] = fac[i - 1] * mint(i);
    inv[i] = (-inv[mint::get_mod() % i]) * mint(mint::get_mod() / i);
    ifac[i] = ifac[i - 1] * inv[i];
  }
}

inline mint C(int x, int y) {
  if (y < 0 || y > x) return 0;
  return fac[x] * ifac[y] * ifac[x - y];
}
template<typename T>
void fwt(T *a, int len) {
  for (int i = 1; i < len; i <<= 1) {
    for (int j = 0; j < len; j += i << 1) {
      for (int k = j; k < j + i; ++k) {
        a[k + i] += a[k];
      }
    }
  }
}

template<typename T>
void ifwt(T *a, int len) {
  for (int i = 1; i < len; i <<= 1) {
    for (int j = 0; j < len; j += i << 1) {
      for (int k = j; k < j + i; ++k) {
        a[k + i] -= a[k];
      }
    }
  }
}

template<typename T>
void fmt(T *a, int len) {
  for (int i = 1; i < len; i <<= 1) {
    for (int j = 0; j < len; j += i << 1) {
      for (int k = j; k < j + i; ++k) {
        a[k] += a[k + i];
      }
    }
  }
}

int a[20], b[10000];
int c[20][10000];

void solve() {
  init();
  int n = rd(), m = rd();
  FOR(i, 0, n) a[i] = rd();
  FOR(i, 0, m) b[i] = rd();
  FOR(i, 0, n) FOR(j, 0, m) c[i][j] = rd();
  FOR(i, 0, 1 << n) FOR(j, 0, n) f[i] += ((i & (1 << j)) != 0) * a[j];
  FOR(i, 0, m) {
    int t = 0;
    ROF(j, 0, n) t = (t << 1) | c[j][i];
    g[t] += b[i];
  }
  fwt(g, 1 << n);
  int X = 1e9;
  FOR(i, 0, 1 << n) {
    if (g[i]) chkmin(X, f[i] - g[i]);
  }
  if (X < 0) {
    puts("0 1");
    return;
  }
  FOR(i, 0, 1 << n) {
    if (g[i] && f[i] - g[i] == X) flag[i] = 1;
  }
  fmt(flag, 1 << n);
  FOR(i, 0, 1 << n) h[i] = C(f[i], X + 1);
  ifwt(h, 1 << n);
  mint ans(0);
  FOR(i, 0, 1 << n) if (flag[i]) ans += h[i];
  cout << X + 1 << ' ' << ans << '\n';
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
