// Original Author: misaka18931
// Date: 03-18-21
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
#define MX 200005
#define r first
#define c second
typedef pair<int, int> pt;

pt a[MX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i].r;
  for (int i = 0; i < n; ++i)
    cin >> a[i].c;
  sort (a, a + n, [] (auto a, auto b) { return a.r < b.r; });
  pt curr = make_pair(1, 1);
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    const pt &to = a[i];
    if (curr.r - curr.c == to.r - to.c)
      ans += (to.r - curr.r) * (~(curr.c + curr.r) & 1);
    else {
      if (~(curr.c + curr.r) & 1) curr.r++;
      ans += (((to.r - to.c) - (curr.r - curr.c)) + 1) / 2;
    }
    curr = to;
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
