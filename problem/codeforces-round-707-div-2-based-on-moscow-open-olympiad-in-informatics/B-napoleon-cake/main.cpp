// Original Author: misaka18931
// Date: 03-13-21
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
#define MX 200005

int a[MX];
bool ans[MX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  int den = 0;
  for (int i = n - 1; i >= 0; --i) {
    den = max(den, a[i]);
    ans[i] = den;
    --den;
  }
  for (int i = 0; i < n; ++i) {
    cout << ans[i] << ' ';
  
  cout << endl;
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
