// Original Author: misaka18931
// Date: 01-02-21
// tag: greedy
// AC

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#define MX
using std::cin;
using std::cout;
using std::endl;
using std::memset;
typedef long long LL;
typedef unsigned long long ULL;

LL t[200005];

void solve() {
  int n;
  cin >> n;
  LL delta = 0;
  for (LL i = 0, a, b; i < n; ++i) {
    cin >> a >> b;
    delta += a;
    t[i] = -(a * 2 + b);
  }
  std::sort(t, t + n);
  int ans = 0;
  while (delta >= 0) {
    delta += t[ans];
    ++ans;
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
