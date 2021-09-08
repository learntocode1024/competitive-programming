#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#include "utils"
#include "io"

using bst = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

const int N = 400005;
const i64 mod = 998244353;
i64 fac[N], ifac[N], inv[N];
void init() {
  fac[0] = ifac[0] = fac[1] = ifac[1] = inv[1] = 1;
  for (int i = 2; i < N; ++i) {
    fac[i] = fac[i - 1] * i % mod;
    inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    ifac[i] = ifac[i - 1] * inv[i] % mod;
  }
}

inline i64 C(int n, int k) {
  if (k < 0 || k > n) return 0;
  return fac[n] * ifac[k] % mod * ifac[n - k] % mod;
}

bst T;

int pos[N], sgn[N];
int x[N], y[N];

void solve() {
  int n = rd(), m = rd();
  FOR(i, 0, m) {
    y[i] = rd(), x[i] = rd();
  }
  ROF(i, 0, m) {
    auto iter = T.find_by_order(x[i]);
    pos[i] = *iter;
    T.erase(iter);
  }
  FOR(i, 0, m) {
    sgn[pos[i] - 1] = 0;
    sgn[pos[i]] = 1;
  }
  int k = 0;
  FOR(i, 0, m) {
    k += sgn[pos[i] - 1] + sgn[pos[i]];
    sgn[pos[i] - 1] = 0;
    sgn[pos[i]] = 0;
  }
  ROF(i, 0, m) {
    T.insert(pos[i]);
  }
  cout << C(n * 2 - k - 1, n) << '\n';
}

int main() {
  FOR(i, 1, N + 1) {
    T.insert(i);
  }
  IO::init_in();
  init();
  int T = rd();
  while (T--)
    solve();
}