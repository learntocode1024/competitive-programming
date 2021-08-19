
#include <climits>
#include <iostream>

#include "utils"
#include "io"
#include "modint"

typedef MontgomeryModInt<998244353> mint;

const int N = 1 << 20;
int sz[N];
mint dp[N];
int g[25];

int main() {
  IO::init_in();
  int n = rd(), m = rd();
  FOR(i, 0, m) {
    int u = rd() - 1, v = rd() - 1;
    g[u] |= 1 << v;
    g[v] |= 1 << u;
  }
  FOR(i, 0, n) g[i] |= 1 << i;
  for (int i = 1; i < (1 << n); ++i) {
    for (int j = 0; j < n; ++j) {
      if (!(i & (1 << j))) continue;
      chkmax(sz[i], sz[i & (~g[j])] + 1);
    }
  }
  dp[0] = 1;
  for (int i = 1; i < (1 << n); ++i) {
    for (int j = 0; j < n; ++j) {
      if ((i & (1 << j)) && sz[i] == sz[i & (~g[j])] + 1) {
        dp[i] += dp[i & (~g[j])];
      }
    }
    dp[i] *= mint(__builtin_popcount(i)).inverse();
  }
  cout << dp[(1 << n) - 1] << '\n';
}