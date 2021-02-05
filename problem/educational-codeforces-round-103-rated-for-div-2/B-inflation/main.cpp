// Original Author: misaka18931
// Date: 02-05-21
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

void solve() {
  int n, r, p, delta;
  cin >> n >> r >> p;
  int ans = 0;
  for (int i = 1; i < n; ++i) {
    cin >> delta;
    if (delta * 100 > p * r) {
      int tmp = delta + p;
      p = -(int) ( -1e2 * delta / r) + delta;
      ans += p - tmp;
    } else {
      p = p + delta;
    }
  }
  cout << ans LF;
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