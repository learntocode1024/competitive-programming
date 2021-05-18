// Original Author: misaka18931
// Date: 03-03-21
// tag:
// 

#include <cstdio>
#include <cmath>
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
#define MX 100005

int a[MX];

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  sort(a, a + n);
  int maxv, mexv;
  mexv = (a[0] == 0);
  maxv = a[n - 1];
  int flag = 1;
  for (int i = 1; i < n; ++i) {
    mexv += (mexv == a[i]);
  }
  int tmp = ceil(mexv + (float)(maxv - mexv) / 2.0f);
  for (int i = 0; i < n; ++i) {
    if (tmp == a[i]) flag = 0;
  }
  if (mexv < maxv) cout << n + flag * (k > 0) << endl;
  else cout << n + k << endl;
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
