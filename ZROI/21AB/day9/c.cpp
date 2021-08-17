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

#include <cstdio>
#include <vector>
using namespace std;

/********************************* utility ************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
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

/*********************************** solution *********************************/
#define MX 13

#define v vector
int n, m;
int a[15], b[15];
int S, d;
const i64 mod = 998244353;
namespace sub2 {
i64 inv[100];
v<v<v<v<v<v<v<v<i64> > > > > > > > dp(MX, );

void solve() {
  inv[1] = 1;
  for (int i = 2; i < 100; ++i) {
    inv[i] = mod / i * (mod - inv[mod % i]) % mod;
  }
  i64 ans = 0;
  dp[a[0]][a[1]][a[2]][a[3]][b[0]][b[1]][b[2]][b[3]] = 1;
  for (int a0 = a[0]; a0 >= 0; --a0) {
    for (int a1 = a[1]; a1 >= 0; --a1) {
      for (int a2 = a[2]; a2 >= 0; --a2) {
        for (int a3 = a[3]; a3 >= 0; --a3) {
          for (int b0 = b[0]; b0 >= 0; --b0) {
            for (int b1 = b[1]; b1 >= 0; --b1) {
              for (int b2 = b[2]; b2 >= 0; --b2) {
                for (int b3 = b[3]; b3 >= 0; --b3) {
                  int s = a0 + a1 + a2 + a3 + b0 + b1 + b2 + b3;
                  if (s < S - d) continue;
                  if (s == S - d && !b0 && !b1 && !b2 && !b3) {
                    ans = (ans + dp[a0][a1][a2][a3][b0][b1][b2][b3]) % mod;
                  }
                  i64 iv = 1ll * inv[!!a0 + !!a1 + !!a2 + !!a3 + !!b0 + !!b1 + !!b2 + !!b3] * dp[a0][a1][a2][a3][b0][b1][b2][b3] % mod;
                  if (a0 > 0) {
                    dp[a0 - 1][a1][a2][a3][b0][b1][b2][b3] = (dp[a0 - 1][a1][a2][a3][b0][b1][b2][b3] + iv) % mod;
                  }
                  if (a1 > 0) {
                    dp[a0][a1 - 1][a2][a3][b0][b1][b2][b3] = (dp[a0][a1 - 1][a2][a3][b0][b1][b2][b3] + iv) % mod;
                  }
                  if (a2 > 0) {
                    dp[a0][a1][a2 - 1][a3][b0][b1][b2][b3] = (dp[a0][a1][a2 - 1][a3][b0][b1][b2][b3] + iv) % mod;
                  }
                  if (a3 > 0) {
                    dp[a0][a1][a2][a3 - 1][b0][b1][b2][b3] = (dp[a0][a1][a2][a3 - 1][b0][b1][b2][b3] + iv) % mod;
                  }
                  if (b0 > 0) {
                    dp[a0][a1][a2][a3][b0 - 1][b1][b2][b3] = (dp[a0][a1][a2][a3][b0 - 1][b1][b2][b3] + iv) % mod;
                  }
                  if (b1 > 0) {
                    dp[a0][a1][a2][a3][b0][b1 - 1][b2][b3] = (dp[a0][a1][a2][a3][b0][b1 - 1][b2][b3] + iv) % mod;
                  }
                  if (b2 > 0) {
                    dp[a0][a1][a2][a3][b0][b1][b2 - 1][b3] = (dp[a0][a1][a2][a3][b0][b1][b2 - 1][b3] + iv) % mod;
                  }
                  if (b3 > 0) {
                    dp[a0][a1][a2][a3][b0][b1][b2][b3 - 1] = (dp[a0][a1][a2][a3][b0][b1][b2][b3 - 1] + iv) % mod;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  printf("%lld\n", ans);
}
}  // namespace sub2

void solve() {
  scanf("%d%d%d", &n, &m, &d);
  for (int i = 0; i < n; ++i) {
    scanf("%d", a + i);
    S += a[i];
  }
  for (int j = 0; j < m; ++j) {
    scanf("%d", b + j);
    S += b[j];
  }
  if (n <= 4 && m <= 4) {
    sub2::solve();
  }
}

int main() {
#ifdef MULTI
  int T = IO::rd();
  while (T--) solve();
#else
  solve();
#endif
  return 0;
}
