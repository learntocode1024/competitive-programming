#include <algorithm>
#include <iostream>

#include "utils"
#include "io"
#include "modint"

typedef MontgomeryModInt<1000000007> mint;
const int N = 3605, NN = 300005;
mint dp[N];

mint inv[NN], fac[NN], ifac[NN];

void init() {
  fac[0] = fac[1] = ifac[0] = ifac[1] = inv[1] = 1;
  for (int i = 2; i < NN; ++i) {
    fac[i] = fac[i - 1] * mint(i);
    inv[i] = (-inv[mint::get_mod() % i]) * mint(mint::get_mod() / i);
    ifac[i] = ifac[i - 1] * inv[i];
  }
}

inline mint C(int n, int m) {
  if (m < 0 || m > n) return mint(0);
  return fac[n] * ifac[n - m] * ifac[m];
}

pii a[N];
int lim[N];

int main() {
  IO::init_in();
  init();
  int h = rd(), w = rd(), n = rd();
  a[0] = mkp(1, 1);dp[0] = 1;
  lim[0] = 1;
  for (int i = 1, p, q; i <= n; ++i) p = rd(), q = rd(), a[i] = mkp(p, q);
  ++n;
  a[n] = mkp(h, w);
  ++n;
  sort(a, a + n);
  for (int i = 1; i < n; ++i) {
    dp[i] = C(a[i].fi + a[i].se - 2, a[i].fi - 1);
    for (int j = 1; j < i; ++j) {
      if (a[j].se > a[i].se) continue;
      int dx = a[i].fi - a[j].fi, dy = a[i].se - a[j].se;
      dp[i] -= dp[j] * C(dx + dy, dx);
    }
  }
  cout << dp[n - 1] << endl;
}
