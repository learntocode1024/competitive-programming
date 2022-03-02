// Original Author: misaka18931
// Date: 03-17-21
// tag:
// 

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 1e9 + 7;
#define LF << '\n'
#define SPC << ' '
#define CLRBUF cout << endl;
#define MX 100005

int cnt[MX];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    cnt[i] = 0;
  }
  for (int i = 0; i < n; ++i) {
    int t;
    cin >> t;
    ++cnt[t % m];
  }
  int ans = (cnt[0] > 0);
  for (int i = 1; i <= m / 2; ++i) {
    ans += abs(cnt[i] - cnt[m - i]) + (cnt[i] == cnt[m - i] && cnt[i]);
  }
  cout << ans << endl;
}

int main() {
  cin.tie(NULL);
  std::ios::sync_with_stdio(false);
  int T = 1;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
