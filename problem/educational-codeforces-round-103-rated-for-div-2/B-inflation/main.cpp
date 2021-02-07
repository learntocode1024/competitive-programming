// Original Author: misaka18931
// Date: 02-05-21
// tag: greedy, simple-math
// AC

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
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
  LL n, r, p, delta;
  cin >> n >> r >> p;
  LL ans = 0;
  for (int i = 1; i < n; ++i) {
    cin >> delta;
    ans = max(ans, (LL)ceil(100 * (float) delta / r) - p);
    p += delta;
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