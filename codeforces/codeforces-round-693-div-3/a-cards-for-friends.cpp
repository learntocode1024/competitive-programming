// Original Author: misaka18931
// Date: 01-04-21
// tag:
// 

#include <cstdio>
#include <cstring>
#include <iostream>
#define MX
using std::cin;
using std::cout;
using std::endl;
using std::memset;
typedef long long LL;
typedef unsigned long long ULL;
const int mod = 1e9 + 7;

void solve() {
  int a, b, c;
  cin >> a >> b >> c;
  int p, q;
  q = p = 1;
  while (~a & 1) a >>= 1, p *= 2;
  while (~b & 1) b >>= 1, q *= 2;
  if (p * q >= c) cout << "YES\n";
  else
    cout << "NO\n";
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
