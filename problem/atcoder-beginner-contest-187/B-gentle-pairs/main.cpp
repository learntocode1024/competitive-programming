// Original Author: misaka18931
// Date: 01-02-21
// tag: brute-force
// AC

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define MX
using std::cin;
using std::cout;
using std::endl;
using std::memset;
typedef long long LL;
typedef unsigned long long ULL;
const int mod = 1e9 + 7;

std::pair<int, int> a[1005];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i].first >> a[i].second;
  }
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      if(std::abs(a[j].first - a[i].first) >=
        std::abs(a[j].second - a[i].second)) ++ans;
    }
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
