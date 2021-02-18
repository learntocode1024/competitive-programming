// Original Author: misaka18931
// Date: 02-12-21
// tag: math(sum)
// AC

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
  LL x, y;
  cin >> x >> y;
  LL ans = 0;
  // a = d * (r + 1) ,(d < r)
  // if either a or r is dirricult, why not try d?
  for (LL d = 1; d * (d + 1) <= x; ++d) {
    ans += max(0ll, min(y, x / d - 1) - d);
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