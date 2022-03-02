// Original Author: misaka18931
// Date: 03-17-21
// tag: greedy, STL, brute_force, index
// AC

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
using namespace std;
#define LF << '\n'
#define SPC << ' '
#define CLRBUF cout << endl;
#define MX

int s[4000], tot = -1;
int a[200005];
map<int, int> mp;
int ans[25];
int L[25];

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; ++i) {
    int t;
    cin >> t;
    int *p = lower_bound(s, s + tot, t);
    while (p >= s) {
      if (t % *p == 0) {
        t /= *p;
        break;
      }
      --p;
    }
    a[i] = t;
  }
  mp = map<int, int>();
  for (int i = 0; i <= k; ++i) {
    ans[i] = 1, L[i] = 0;
  }
  for (int i = 0; i < n; ++i) {
    for (int j = min(k, i + 1); j >= 0; --j) {
      if (mp[a[i]] - 1 >= L[j]) {
        ++ans[j];
        L[j] = i; // set this mask instead of brute-force clearing the map
      }
      if (j && ans[j] > ans[j - 1])
        ans[j] = ans[j - 1], L[j] = L[j - 1];
      if (j && ans[j] == ans[j - 1])
        L[j] = max(L[j], L[j - 1]);
    }
    mp[a[i]] = i + 1;
  }
  int t = n;
  for (int i = 0; i <= k; ++i) {
    t = min(t, ans[i]);
  }
  cout << t << endl;
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
