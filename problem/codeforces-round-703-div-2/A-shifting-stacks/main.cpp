// Original Author: misaka18931
// Date: 02-18-21
// tag: array-process
// AC

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
  if ((bool)x) printf("YES\n"); \
  else printf("NO\n");
#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define max(X, Y)  ((X) > (Y) ? (X) : (Y))
#define MX 105

LL a[MX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    a[i] -= i;
  }
  LL k = 0;
  for (int i = 0; i < n; ++ i) {
    if (a[i] > 0) k += a[i];
    else {
      if (a[i] + k < 0) {
        printb(0)
        return;
      }
      k += a[i];
    }
  }
  printb(1)
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
