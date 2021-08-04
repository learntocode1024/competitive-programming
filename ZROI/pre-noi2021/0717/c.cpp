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
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 998244353;

#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define MX 200005

template<typename T>
void chkmax(T &a, const T &b) {
  a = max(a, b);
}
template <typename T>
void chkmin(T &a, const T &b) {
  b = min(a, b);
}

LL n;
LL f[MX];

LL inv[MX], fac[MX], ifac[MX];

LL C(int n, int m) {
  if (n < m) return 0;
  if (m < 0 || n < 0) return 0;
  return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
} 

inline void prework() {
  inv[1] = fac[1] = fac[0] = ifac[0] = ifac[1] = 1;
  for (int i = 2; i <= n; ++i) {
    fac[i] = fac[i - 1] * i % mod;
    inv[i] = (mod - mod / i * inv[mod % i] % mod) % mod;
    ifac[i] = ifac[i - 1] * inv[i] % mod;
  }
}

namespace SUBTASK50 {
LL S[5005][5005];

void prework() {
  S[1][1] = 1;
  for (int i = 2; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      S[i][j] = (S[i - 1][j - 1] + j * S[i - 1][j]) % mod;
    }
  }
}

inline void solve() {
  prework();
  printf("%lld ", f[n]);
  for (LL k = 1; k < n; ++k) {
    LL ans = 0;
    for (int u = 1; u <= n - k; ++u) {
      ans += f[u] * C(n, u) % mod * S[n - u][k] % mod;
      ans %= mod;
    }
    printf("%lld ", ans);
  }
  puts("");
}
} // namespace SUBTASK50

inline void solve() {
  scanf("%lld", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", f + i);
  }
  prework();
  if (n <= 5000) SUBTASK50::solve();
}

int main() {
  int T = 1;
  while (T--)
    solve();
  return 0;
}
