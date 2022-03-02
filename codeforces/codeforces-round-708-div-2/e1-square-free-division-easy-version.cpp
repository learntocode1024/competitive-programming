// Original Author: misaka18931
// Date: 03-17-21
// tag:
// 

#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;
#define LF << '\n'
#define SPC << ' '
#define CLRBUF cout << endl;
#define MX

int s[4000], tot = -1;
int a[200005];
set<int> mp;

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; ++i) {
    int t;
    cin >> t;
    int* p = lower_bound(s, s + tot, t);
    while (p >= s) {
      if (t % *p == 0) {
        t /= *p;
        break;
      }
      --p;
    }
    a[i] = t;
  }
  int ans = 1;
  for (int i = 0; i < n; ++i) {
    if (mp.count(a[i])) {
      ++ans;
      mp.clear();
    }
    mp.insert(a[i]);
  }
  mp.clear();
  cout << ans << endl;
}

int main() {
  cin.tie(NULL);
  std::ios::sync_with_stdio(false);
  int T = 1;
  cin >> T;
  for (int i = 1; i * i < 10000007; ++i) {
    s[++tot] = i * i;
  }
  while (T--) {
    solve();
  }
  return 0;
}
