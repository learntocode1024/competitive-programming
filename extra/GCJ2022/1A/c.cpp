#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int x[N][N];
int mn[N][N][N];
int E, W;
int f[N][N];

void solve() {
  cin >> E >> W;
  for (int i = 1; i <= E; ++i) for (int j = 1; j <= W; ++j) cin >> x[i][j];
  for (int i = 1; i <= E; ++i) {
    for (int j = 1; j <= W; ++j) mn[i][i][j] = x[i][j];
    for (int j = i + 1; j <= E; ++j) {
      for (int k = 1; k <= W; ++k)
        mn[i][j][k] = min(mn[i][j-1][k], x[j][k]);
    }
  }
  for (int len = 2; len <= E; ++len) {
    for (int l = 1; l + len <= E + 1; ++l) {
      int r = l + len - 1;
      f[l][r] = 11451419;
      for (int m = l; m < r; ++m) {
        int cur = f[l][m] + f[m+1][r];
        for (int k = 1; k <= W; ++k) {
          cur += mn[l][m][k] - mn[l][r][k];
          cur += mn[m+1][r][k] - mn[l][r][k];
        }
        f[l][r] = min(f[l][r], cur);
      }
    }
  }
  int ans = f[1][E];
  for (int i = 1; i <= W; ++i) ans += mn[1][E][i];
  cout << ans * 2 << '\n';
}

int main() {
    int T;
    cin >> T;
    for (int i = 1; i <= T; ++i) {
        cout << "Case #" << i << ": ";
        solve();
    }
}
