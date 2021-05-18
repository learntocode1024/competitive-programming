// Original Author: misaka18931
// Date: 03-01-21
// tag:
// 

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
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
#define MX 200005

string s, t;
int prf[MX], suf[MX];

void solve() {
  int n, m;
  cin >> n >> m >> s >> t;
  for (int i = 0, j = 0; i < m && j < n; ++i) {
    while (s[j] != t[i]) ++j;
    prf[i] = j;
    ++j;
  }
  for (int i = m - 1, j = n - 1;i >= 0 && j >= 0; --i) {
    while (s[j] != t[i]) --j;
    suf[i] = j;
    --j;
  }
  int ans = 0;
  for (int i = 0; i < m - 1; ++i) {
    ans = max(ans, suf[i + 1] - prf[i]);
  }
  cout << ans << endl;
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
