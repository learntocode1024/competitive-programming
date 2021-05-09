// Original Author: misaka18931
// Date: $DATE
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
#define printb(x) \
  if ((bool)x) printf("YES"); \
  else printf("NO");
#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define MX

void solve() {
  int n;
  cin >> n;
  LL minv = 1e9 + 7, minp = -1;
  for (int i = 1; i <= n; ++i) {
    LL tmp;
    cin >> tmp;
    if (tmp < minv) minv = tmp, minp = i;
  }
  cout << n - 1 << endl;
  for (int i = 1; i < minp; ++i) {
    cout << i << ' ' << minp << ' ' << minv + minp - i << ' ' << minv << endl;
  }
  for (int i = minp + 1; i <= n; ++i) {
    cout << i << ' ' << minp << ' ' << minv + i - minp << ' ' << minv << endl;
  }
}

int main() {
  int T = 1;
  cin >> T;
  while (T--)
    solve();
  return 0;
}

