#include <iostream>

#include "io"
#include "utils"
#include "modint"

using mint = MontgomeryModInt<998244353>;

const int N = 105, M = 2005;

mint a[N][M], s[N], dp[N][N << 1];

int main() {
  IO::init_in();
  int n = rd(), m = rd();
  FOR(i, 0, n) FOR(j, 0, m) a[i][j] = rd();
  FOR(i, 0, n) FOR(j, 0, m) s[i] += a[i][j];
  mint ans(1);
  FOR(i, 0, n) ans *= (s[i] + 1);
  ans -= 1;
  dp[0][n] = 1;
  FOR(c, 0, m) {
    FOR(i, 0, n) {
      mint th = a[i][c], oth = s[i] - th;
      dp[i + 1][0] = dp[i][0] + dp[i][1] * oth;
      dp[i + 1][n << 1] = dp[i][n << 1] + dp[i][(n << 1) - 1] * th;
      FOR(j, 1, n << 1) {
        dp[i + 1][j] = dp[i][j] + dp[i][j - 1] * th + dp[i][j + 1] * oth;
      }
    }
    FOR(i, n, n << 1) ans -= dp[n][i + 1];
  }
  cout << ans << '\n';
  return 0;
}