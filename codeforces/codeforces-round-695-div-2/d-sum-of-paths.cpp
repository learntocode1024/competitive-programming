// Original Author: misaka18931
// Date: 01-08-21
// tag: dp(n^2), brute-force
// AC

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define LF << '\n'
#define SPC << ' '
#define CLRBUF cout << endl;
#define MX 5005
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 1e9 + 7;

inline void print(const bool &b) {
  if (b) cout << "YES" << endl;
  else cout << "NO" << endl;
}

LL a[MX];
LL c[MX];
LL ans = 0;
LL dp[MX][MX];

void solve() {
  LL pos, t;
  cin >> pos >> t;
  ans = (ans + c[pos] * (t - a[pos]) % mod) % mod;
  if (ans < 0) ans = mod + ans;
  cout << ans << endl;
  a[pos] = t;
}

int main() {
  cin.tie(NULL);
  std::ios::sync_with_stdio(false);
  int n, k;
  cin >> n >> k;
  ++k;
  int T = 1;
  cin >> T;
  for (int i = 1; i <= n; ++i) {
    dp[0][i] = 1;
  }
  for (int i = 1; i < k; ++i) {
    for (int j = 1; j <= n; ++j) {
      dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j + 1]) % mod;
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < k; ++j) {
      c[i] = (c[i] + dp[j][i] * dp[k - j - 1][i] % mod) % mod;
    }
  }
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; ++i) {
    ans = (ans + c[i] * a[i] % mod) % mod;
  }
  while (T--) {
    solve();
  }
  return 0;
}
