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
#include <map>
#include <string>
#include <vector>
using namespace std;

#include "utils"
#include "io"
#include "modint"
using mint = MontgomeryModInt<998244353>;

const int N = 50005;
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

inline mint iC(int x, int y) {
  if (y < 0 || y > x) return 0;
  return ifac[x] * fac[y] * fac[x - y];
}

map<int, int> c;
int cnt[N], tot;
int b[N], d[N], t;

void solve() {
  init();
  int n = rd();
  FOR(i, 0, n)
    ++ c[rd()];
  for (auto i : c) {
    cnt[tot++] = i.second;
  }
  sort(cnt, cnt + tot);
  FOR(i, 0, tot) {
    b[t] = cnt[i];
    ++d[t];
    if (cnt[i] != cnt[i + 1]) ++t;
  }
  FOR(k, 1, n + 1) {
    mint ans = 0;
    FOR(i, 0, t) {
      ans += C(n - b[i], k) * d[i];
    }
    ans = -ans * iC(n, k) + tot;
    cout << ans << '\n';
  }
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
