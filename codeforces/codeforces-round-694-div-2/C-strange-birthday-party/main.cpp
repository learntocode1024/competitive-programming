// Original Author: misaka18931
// Date: 01-04-21
// tag:
// 

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define MX 300005
using std::cin;
using std::cout;
using std::endl;
using std::memset;
typedef long long LL;
typedef unsigned long long ULL;
const int mod = 1e9 + 7;

int k[MX];
LL c[MX];

bool cmp(const LL &a, const LL &b) {
  return (a > b);
}

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    cin >> k[i];
  }
  for (int i = 1; i <= m; ++i) {
    cin >> c[i];
  }
  int curr = 1;
  LL ans = 0;
  std::sort(k, k + n, cmp);
  for (int i = 0; i < n; ++i) {
    if (curr < k[i]) {
      ans += c[curr++];
    } else {
      ans += c[k[i]];
    }
  }
  cout << ans << endl;
  for (int i = 0; i < n; ++i) {
    k[i] = 0;
  }
  for (int i = 0; i < m; ++i) {
    c[i] = 0;
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
