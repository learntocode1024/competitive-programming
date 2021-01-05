// Original Author: misaka18931
// Date: 01-04-21
// tag:
// 

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define MX 100005
using std::cin;
using std::cout;
using std::endl;
using std::memset;
typedef long long LL;
typedef unsigned long long ULL;
const int mod = 1e9 + 7;

LL a[MX];

void solve() {
  LL n, x;
  cin >> n >> x;
  int mint, minv = __INT32_MAX__;
  LL tmp, sum = 0;
  for (int i = 0; i < n; ++i) {
    cin >> tmp;
    sum += tmp;
    a[i] = tmp;
    int cnt = 0;
    while (tmp % x == 0) tmp /= x, ++cnt;
    if (cnt < minv) minv = cnt, mint = i;
  }
  ULL ans = sum * minv + sum;
  for (int i = 0; i < mint; ++i) {
    ans += a[i];
  }
  cout << ans << endl;
  for (int i = 0; i < n; ++i) {
    a[i] = 0;
  }
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
