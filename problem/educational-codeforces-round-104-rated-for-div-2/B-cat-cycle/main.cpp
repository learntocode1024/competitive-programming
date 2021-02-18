// Original Author: misaka18931
// Date: 02-15-21
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
#define LF << '\n'
#define SPC << ' '
#define CLRBUF cout << endl;
#define init(T, x) \
  T x; \
  cin >> x;
#define printb(x) \
  if ((bool)x) printf("YES"); \
  else printf("NO");
#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define max(X, Y)  ((X) > (Y) ? (X) : (Y))
#define MX


void solve() {
  int n;
  LL k;
  cin >> n >> k;
  if (n & 1) {
    LL t = n / 2;
    LL ans = (1ll * (k - 1) / t * (t + 1) + (k - 1) % t) % n;
    cout << ans + 1 << endl;
  } else {
    cout << (k - 1) % n + 1 << endl;
  }
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
