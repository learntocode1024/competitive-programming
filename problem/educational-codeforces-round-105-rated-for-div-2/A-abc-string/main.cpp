// Original Author: misaka18931
// Date: 03-02-21
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
  if ((bool)x) printf("YES\n"); \
  else printf("NO\n");
#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define max(X, Y)  ((X) > (Y) ? (X) : (Y))
#define MX
string s;

void solve() {
  cin >> s;
  char a = s[0], b = 0;
  int b1, b2, b3;
  int c1, c2, c3;
  c1 = c2 = c3 = 0;
  b1 = b2 = b3 = 1;
  for (auto i : s) {
    if (!b && i != a) b = i;
    if (b1 + b2 + b3 == 0) break;
    if (i == a) ++c1, ++c2, ++c3;
    else if (i == b) --c1, ++c2, --c3;
    else ++c1, --c2, --c3;
    if (c1 < 0) b1 = 0;
    if (c2 < 0) b2 = 0;
    if (c3 < 0) b3 = 0;
  }
  printb((b1 && c1 == 0) + (b2 && c2 == 0) + (b3 && c3 == 0))
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
