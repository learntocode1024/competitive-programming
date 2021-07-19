/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Jul 19, 2021
 * Algorithm: combinatorics
 * Difficulty: easy
 *
 *********************************************************************/

#include <algorithm>
#include <cstdint>
#include <climits>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 998244353;

#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define MX 5000005

template<typename T>
void chkmax(T &a, const T &b) {
  a = max(a, b);
}
template <typename T>
void chkmin(T &a, const T &b) {
  b = min(a, b);
}

LL inv[MX], fac[MX], ifac[MX];

LL C(int n, int m) {
  if (n < m) return 0;
  if (m < 0 || n < 0) return 0;
  return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
} 

inline void prework(int n) {
  inv[1] = fac[1] = fac[0] = ifac[0] = ifac[1] = 1;
  for (int i = 2; i <= n; ++i) {
    fac[i] = fac[i - 1] * i % mod;
    inv[i] = (mod - mod / i * inv[mod % i] % mod) % mod;
    ifac[i] = ifac[i - 1] * inv[i] % mod;
  }
}

int T, m;
int a[105];
int cnt[105];

void solve() {
  scanf("%d", &m);
  int n = 0;
  LL ans = 1;
  for (int i = 0; i < m; ++i) {
    int  x;
    scanf("%d", &x);
    a[i] = x;
    ans = ans * ifac[x] % mod;
    n += x;
    ++cnt[x];
  }
  for (int i = 1; i <= 100; ++i) {
    ans = ans * ifac[cnt[i]] % mod;
  }
  LL inv = ans;
  ans = ans * fac[n] % mod;
  for (int i = 1; i <= 100; ++i) {
    if (cnt[i] != 0) {
      LL curr = inv * fac[n - i] % mod * fac[i] % mod * cnt[i] % mod;
      ans = (ans + mod - curr) % mod;
    }
  }
  printf("%lld\n", ans);
}

int main() {
  prework(100);
  scanf("%d", &T);
  while (T--) {
    solve();
  }
  return 0;
}

