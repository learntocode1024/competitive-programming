// Original Author: misaka18931
// Date: 02-18-21
// tag: binary-search
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
  if ((bool)x) printf("YES"); \
  else printf("NO");
#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define max(X, Y)  ((X) > (Y) ? (X) : (Y))
#define MX

inline int query(const int &l, const int &r) {
  cout << "? " << l + 1 << " " << r << endl;
  cout.flush();
  int ans;
  cin >> ans;
  return ans - 1;
}

int solve() {
  int n;
  cin >> n;
  int second = query(0, n);
  if (second == n - 1 || (second && second == query(0, second + 1))) {
    // [0, second)
    if (second == 1) return 0;
    int l = 0, r = second, mid;
    while (r - l > 1) { // [l, r)
      mid = l + (r - l) / 2;
      if (query(mid, second + 1) == second) // [mid, second]
        l = mid;
      else r = mid; // [l, mid)
    }
    return l;
  } else { // right
    // [second + 1, n)
    if (second == n - 2) return n - 1;
    int l = second + 1, r = n, mid;
    while (r - l > 1) {
      mid = l + (r - l) / 2;
      if (query(second, mid) == second) // [second, mid)
        r = mid;
      else l = mid;
    }
    return l;
  }
}

int main() {
  cin.tie(NULL);
  std::ios::sync_with_stdio(false);
  int T = 1;
  // cin >> T;
  while (T--) {
    printf("! %d\n", solve() + 1);
    fflush(stdout);
  }
  return 0;
}
