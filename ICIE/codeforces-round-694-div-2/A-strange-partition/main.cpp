// Original Author: misaka18931
// Date: 01-04-21
// tag: easy
// AC

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
  LL n, x;
  cin >> n >> x;
  LL a, b, c;
  a = b = 0;
  for (int i = 0; i < n; ++i) {
    cin >> c;
    a += c;
    b += c / x + (bool)(c % x);
  }
  a = a / x + (bool)(a % x);
  cout << a << " " << b << endl;
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
