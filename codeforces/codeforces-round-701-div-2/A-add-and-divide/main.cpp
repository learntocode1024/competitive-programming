// Original Author: misaka18931
// Date: 02-12-21
// tag:
//

#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#define LF << '\n'
#define SPC << ' '
#define CLRBUF cout << endl;
#define MX
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 1e9 + 7;

inline void print(const bool &b) {
  if (b)
    cout << "YES" << endl;
  else
    cout << "NO" << endl;
}

inline int log(LL a, LL b) {
  int ans = 0;
  while (++ans && (a /= b))
    ;
  return ans;
}

int n, k;
inline int calc(int x) {
  if (x == 1)
    return INT_MAX;
  return (x - k + log(n, x));
}

void solve() {
  cin >> n >> k;
  if (n < k)
    cout << 1 << endl;
  else if (n == k)
    cout << 2 << endl;
  else {
    int l = k;
    int r = 1e9 + 7;
    while ((r - l) / 3) {
      int lmid = l + (r - l) / 3;
      int rmid = r - (r - l) / 3;
      if (calc(lmid) >= calc(rmid)) {
        l = lmid;
      } else {
        r = rmid;
      }
    }
    cout << min(calc(l), min(calc(l + 1), calc(r))) << endl;
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
