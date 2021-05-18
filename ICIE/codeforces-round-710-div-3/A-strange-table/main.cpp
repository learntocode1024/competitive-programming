// Original Author: misaka18931
// Date: 03-18-21
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
#define MX


void solve() {
  LL n, m, x;
  LL s1, s2;
  cin >> n >> m >> x;
  --x;
  s1 = x / n;
  s2 = x % n;
  cout << s2 * m + s1 + 1 << endl;
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
