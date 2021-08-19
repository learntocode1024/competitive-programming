#include <iostream>

#include "utils"
#include "io"

int main() {
  IO::init_in();
  int n = rd(), m = rd();
  static char s[100005];
  IO::rdstr(s);
  static int g[20][20];
  for (int i = 0; i < n - 1; ++i) {
    ++g[s[i] - 'a'][s[i + 1] - 'a'];
    ++g[s[i + 1] - 'a'][s[i] - 'a'];
  }
  static i64 dp[1 << 20];
  for (int i = 1; i < 1 << m; ++i) {
    dp[i] = INT64_MAX;
    int cnt = 0;
    for (int j = 0; j < m; ++j) {
      if (i & (1 << j)) ++cnt;
    }
    for (int j = 0; j < m; ++j) {
      if (i & (1 << j)) {
        i64 cur = dp[i - (1 << j)];
        for (int k = 0; k < m; ++k) {
          if (k == j) continue;
          if (i & (1 << k)) cur += g[j][k] * cnt;
          else cur -= g[j][k] * cnt; // break down the distance to +pos and -pos parts!
        }
        chkmin(dp[i], cur);
      }
    }
  }
  cout << dp[(1 << m) - 1] << '\n';
}
