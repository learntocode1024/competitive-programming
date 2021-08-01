// Original Author: misaka18931
// Date: 03-03-21
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
#define MX 100005

int a[MX];
int top[MX], asc[MX], rasc[MX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i < n; ++i) {
    if (a[i] > a[i - 1]) asc[i] = asc[i - 1] + 1;
    else ++top[i - 1];
  }
  for (int i = n - 2; i >= 0; --i) {
    if (a[i] > a[i + 1]) rasc[i] = rasc[i + 1] + 1;
    else ++top[i + 1];
  }
  int maxv = 0, maxp, maxv2 = 0;
  for (int i = 0; i < n; ++i) {
    if (max(asc[i], rasc[i]) > maxv) maxv = max(asc[i], rasc[i]), maxp = i;
  }
  for (int i = 0; i < n; ++i) {
    if (i == maxp) continue;
    if (max(asc[i], rasc[i]) > maxv2)
      maxv2 = max(asc[i], rasc[i]);
  }
  int ans = 0;
  for (int i = 1; i < n - 1; ++i) {
    if (top[i] < 2) continue; 
    int c = max(asc[i], rasc[i]);
    int b = min(asc[i], rasc[i]);
    int curr = (i == maxp) ? (c > maxv2) : (c > maxv);
    c -= ((~c) & 1);
    ans += curr * (c < b);
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
