// Original Author: misaka18931
// Date: 01-02-21
// tag: dp(binary-compress)
// 

#include <cstdio>
#include <cstring>
#include <iostream>
#define MX 20
using std::cin;
using std::cout;
using std::endl;
using std::memset;
typedef long long LL;
typedef unsigned long long ULL;

int n, m;
bool G[MX][MX];
int dp[1 << 18];

int calc(int x) {
  if (dp[x]) return dp[x];
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    if (x & (1 << i)) {

    }
  }
}

void solve() {
  cin >> n >> m;
  for (int i = 0, a, b; i < m; ++i) {
    cin >> a >> b;
    G[a][b] = G[b][a] = true;
  }
  cout << calc((1 << n) - 1) << endl;
}

int main() {
  cin.tie(NULL);
  std::ios::sync_with_stdio(false);
  int T = 1;
  // cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
