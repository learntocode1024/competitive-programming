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
#define MX 10//0005

int a[MX], b[MX], tm[MX];
int a1[MX], b1[MX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  for (int i = 0; i < n; ++i) {
    cin >> b[i];
  }
  for (int i = 0; i < n; ++i) {
    cin >> tm[i];
  }
  for (int i = 1; i < n; ++i) {
    tm[i] -= a[i] - b[i - 1];
  }
  b1[0] = b[0];
  for (int i = 1; i < n; ++i) {
    a1[i] = b1[i - 1] + tm[i];
    b1[i] = max(b[i], a1[i] + (int)((b[i] - a[i]) / 2.0f + 0.5f));
  }
  cout << a1[n - 1] << endl;
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
