// Original Author: misaka18931
// Date: 02-12-21
// tag: simple-math
// AC

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define LF << '\n'
#define SPC << ' '
#define CLRBUF cout << endl;
#define MX 100005
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 1e9 + 7;

inline void print(const bool &b) {
  if (b) cout << "YES" << endl;
  else cout << "NO" << endl;
}

int a[MX], b[MX];

void solve() {
  int n, q, k;
  cin >> n >> q >> k;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  a[n + 1] = k + 1;
  for (int i = 1; i <= n; ++i) {
    b[i] = a[i + 1] - a[i - 1] - 2;
  }
  for (int i = 1; i <= n; ++i) {
    b[i] += b[i - 1];
  }
  while (q--) {
    int l, r;
    cin >> l >> r;
    int ans;
    if (r == l) ans = k - 1;
    else ans = b[r] - b[l - 1] + a[l - 1] + k - a[r + 1] + 1;
    cout << ans << endl;
  }
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