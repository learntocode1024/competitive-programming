// Original Author: misaka18931
// Date: 01-08-21
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
  int a, b, c;
  cin >> a >> b >> c;
  LL x, y, z;
  x = y = z = __INT32_MAX__;
  LL sum[3];
  LL ans = 0;
  LL tmp;
  for (int i = 0; i < a; ++i) {
    cin >> tmp;
    ans += tmp;
    x = min(x, tmp);
  }
  sum[0] = ans;
  for (int i = 0; i < b; ++i) {
    cin >> tmp;
    ans += tmp;
    y = min(y, tmp);
  }
  sum[1] = ans - sum[0];
  for (int i = 0; i < c; ++i) {
    cin >> tmp;
    ans += tmp;
    z = min(z, tmp);
  }
  sum[2] = ans - sum[1] - sum[0];
  LL extra = x + y + z - max(x, max(y, z));
  extra = min(extra, min(sum[0], min(sum[1], sum[2])));
  cout << ans - 2 * extra << endl;
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
