// Original Author: misaka18931
// Date: 02-18-21
// tag:
// 

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define LF << '\n'
#define SPC << ' '
#define CLRBUF cout << endl;
#define MX
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 1e9 + 7;

inline void print(const bool &b) {
  if (b) cout << "YES" << endl;
  else cout << "NO" << endl;
}

int c[3];

void solve() {
  int n, ans = 0;
  cin >> n;
  for (int i = 0; i < 3; ++i) {
    c[i] = 0;
  }
  for (int i = 0, t; i < n; ++i) {
    cin >> t;
    ++c[t % 3];
  }
  for (int i = 0; i < 3; ++i) {
    if (c[i] > n / 3) ans += 
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