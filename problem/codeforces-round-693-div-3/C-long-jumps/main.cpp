// Original Author: misaka18931
// Date: 01-04-21
// tag:
// 

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define MX 200005
using std::cin;
using std::cout;
using std::endl;
using std::memset;
typedef long long LL;
typedef unsigned long long ULL;
const int mod = 1e9 + 7;

LL a[MX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i + 1];
  }
  LL ans = 0;
  for (int i = n ; i > 0; --i) {
    if (i + a[i] <= n) a[i] += a[i + a[i]];
    ans = std::max(ans, a[i]);
  }
  cout << ans << endl;
  for (int i = 0; i <= n; ++i) {
    a[i] = 0;
  }
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
