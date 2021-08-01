// Original Author: misaka18931
// Date: 03-18-21
// tag:
// 

#include <cstdio>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 1e9 + 7;
#define MX

map<int, int> cnt;

void solve() {
  int n;
  cin >> n;
  cnt.clear();
  for (int i = 0, t; i < n; ++i) {
    cin >> t;
    ++cnt[t];
  }
  int v = 0;
  for (auto i : cnt) v = max(v, i.second);
  cout << max(n & 1, 2 * v - n) << endl;
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
