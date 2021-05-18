// Original Author: misaka18931
// Date: 02-15-21
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
#define MX


void solve() {
  int n;
  cin >> n;
  if (n & 1) {
    --n;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < min(n / 2, n - i); ++j) {
        cout << "1 ";
      }
      for (int j = n / 2; j < n - i; ++j) {
        cout << "-1 ";
      }
    }
  } else {
    --n;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < min(n / 2, n - i); ++j) {
        cout << "1 ";
      }
      if (n / 2 < n - i)
        cout << "0 ";
      for (int j = n / 2 + 1; j < n - i; ++j) {
        cout << "-1 ";
      }
    }
  }
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
