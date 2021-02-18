// Original Author: misaka18931
// Date: 02-18-21
// tag:
//

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 1e9 + 7;
#define LF << '\n'
#define SPC << ' '
#define CLRBUF cout << endl;
#define init(T, x)                                                             \
  T x;                                                                         \
  cin >> x;
#define printb(x)                                                              \
  if ((bool)x)                                                                 \
    printf("YES");                                                             \
  else                                                                         \
    printf("NO");
#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define min(X, Y) ((X) < (Y) ? (X) : (Y))
#define max(X, Y) ((X) > (Y) ? (X) : (Y))
#define MX

inline int query(const int &l, const int &r) {
  cout << "? " << l + 1 << " " << r << endl;
  cout.flush();
  int ans;
  cin >> ans;
  return ans - 1;
}

int calc(int l, int r, int second) {
  if (r - l == 1)
    return l;
  if (r - l == 2)
    return ((l == second) ? l + 1 : l);
  if (r - l == 3) {
    int a = second;
    if (a == l)
      return (r - 1 == query(l + 1, r) ? l + 1 : r - 1);
    if (a == r - 1)
      return ((l == query(l, r - 1)) ? l + 1 : l);
    if (a == l + 1)
      return ((l == query(l, r - 1)) ? l + 2 : l);
  }
  int mid = l + (r - l) / 2;
  if (second < mid) {
    int val = query(l, mid);
    if (val == second)
      return calc(l, mid, second);
    else
      return calc(mid, r, query(mid, r));
  } else {
    int val = query(mid, r);
    if (val == second)
      return calc(mid, r, second);
    else
      return calc(l, mid, query(l, mid));
  }
}

void solve() {
  int n;
  cin >> n;
  int ans = calc(0, n, query(0, n));
  cout << "! " << ans + 1 << endl;
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
