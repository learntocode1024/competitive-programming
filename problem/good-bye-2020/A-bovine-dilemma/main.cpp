// Original Author: misaka18931
// Date: 12-30-20
// tag:
// AC

#include <cstdio>
#include <cstring>
#include <iostream>
#define MX
using std::cin;
using std::cout;
using std::endl;
using std::memset;
typedef long long LL;
typedef unsigned long long ULL;
const int mod = 1e9 + 7;

int a[50];
bool vis[50];

inline int abs(int x) {
  if (x < 0) return -x;
  return x;
}

void solve() {
  memset(a, 0, sizeof(a));
  memset(vis, 0, sizeof(vis));
  int n;
  cin >> n;
  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int b = abs(a[i] - a[j]);
      if (i != j && !vis[b]) {
        ++cnt;
        vis[b] = true;
      }
    }
  }
  cout << cnt << endl;
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
