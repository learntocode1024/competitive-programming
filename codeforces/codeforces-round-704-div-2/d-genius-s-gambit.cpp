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
const LL mod = 1e9 + 7;
#define LF << '\n'
#define SPC << ' '
#define CLRBUF cout << endl;
#define init(T, x) \
  T x; \
  cin >> x;
#define printb(x) \
  if ((bool)x) printf("Yes\n"); \
  else printf("No\n");
#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define max(X, Y)  ((X) > (Y) ? (X) : (Y))
#define MX

void solve() {
  int a, b, k;
  cin >> a >> b >> k;
  int n = a + b - 1;
  --b;
  int ok = 1;
  if (!b && k) ok = 0;
  if (!a && k) ok = 0;
  if (k && k > n - 1) ok = 0;
  printb(ok)
  if (ok) {
    if (!k) {
      for (int i = -1; i < b; ++i) printf("1");
      if (n - b) printf("%0*d\n", n - b, 0);
      else printf("\n");
      for (int i = -1; i < b; ++i) printf("1");
      if (n - b) printf("%0*d\n", n - b, 0);
      else printf("\n");
      return;
    }
    int b1 = b - 1;
    int p = n - k - 1;
    printf("1");
    for (int i = 0; i < n; ++i) {
      if (b1 && i != p) printf("1"), --b1;
      else if (i == p) printf("1");
      else printf("0");
    }
    printf("\n");
    b1 = b - 1;
    printf("1");
    for (int i = 0; i < n; ++i) {
      if (b1 && i != p)
        printf("1"), --b1;
      else if (i == p)
        printf("0");
      else if (i == n - 1)
        printf("1");
      else
        printf("0");
    }
    printf("\n");
  }
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
