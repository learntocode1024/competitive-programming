// Original Author: misaka18931
// Date: 02-05-21
// tag:
// 

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define LF << '\n'
#define SPC << ' '
#define CLRBUF cout << endl;
#define MX
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 1e9 + 7;

inline void print(const bool &b) {
  if (b) cout << "YES" << endl;
  else cout << "NO" << endl;
}
string s;
void solve() {
  int a, b, c, d;
  a = b = c = d = 0;
  int x, y;
  cin >> x >> y >> s;
  for (auto i : s) {
    if (i == 'U') ++a;
    if (i == 'D') ++b;
    if (i == 'R') ++c;
    if (i == 'L') ++d;
  }
  print(x <= c && x >= -d && y <= a && y >= -b);
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