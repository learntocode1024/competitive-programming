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
  cin >> n;
  int cnt, minv, curr;
  cnt = 1;
  cin >> minv;
  for (register int i = 1; i < n; ++i) {
    cin >> curr;
    if (curr == minv) ++cnt;
    if (curr < minv) {
      minv = curr;
      cnt = 1;
    }
  }
  cout << n - cnt << endl;
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
