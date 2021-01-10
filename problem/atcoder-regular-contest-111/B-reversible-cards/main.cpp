// Original Author: misaka18931
// Date: 01-09-21
// tag:
// 

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define LF << '\n'
#define SPC << ' '
#define CLRBUF cout << endl;
#define MX 400005
using namespace std;
typedef long long LL;

inline void print(const bool &b) {
  if (b) cout << "YES" << endl;
  else cout << "NO" << endl;
}

int vis[MX];
int a[MX], b[MX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i] >> b[i];
    ++vis[a[i]];
  }
  for (int i = 0; i < n; ++i) {
    if (vis[a[i]] > 1 && !vis[b[i]]) {
      --vis[a[i]];
      ++vis[b[i]];
    }
  }
  int ans = 0;
  for (int i = 0; i < MX; ++i) {
    if (vis[i]) ++ans;
  }
  cout << ans << endl;
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
