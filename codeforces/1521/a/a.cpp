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
  LL a, b;
  cin >> a >> b;
  if (b == 1) {
    cout << "NO" << endl;
    return;
  }
  if (b == 2) {
    cout << "YES" << endl << a << ' ' << a * 3 << ' ' << a * b * 2 << endl;
    return;
  }
  cout << "YES" << endl << a << ' ' << a * (b - 1) << ' ' << a * b << endl;
}

int main() {
  int T = 1;
  cin >> T;
  while (T--)
    solve();
  return 0;
}
