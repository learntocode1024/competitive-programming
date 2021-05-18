// Original Author: misaka18931
// Date: 01-28-21
// tag:
// 

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define LF << '\n'
#define SPC << ' '
#define CLRBUF cout << endl;
#define MX 200005
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 1e9 + 7;

inline void print(const bool &b) {
  if (b) cout << "YES" << endl;
  else cout << "NO" << endl;
}

LL d[MX], t[MX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < 2 * n; ++i) {
    cin >> d[i];
  }
  for (int i = 0; i < 2 * n; ++i) {
    if (d[i] & 1) {
      print(false);
      return;
    }
  }
  sort(d, d + 2 * n);
  LL* p = unique(d, d + 2 * n);
  if ((p - d) != n) {
    print(false);
    return;
  }
  LL s = 0;
  for (int i = 1; i < n; ++i) {
    t[i] = (d[i] - d[i - 1]) / i;
    if (t[i] * i < (d[i] - d[i - 1]) || t[i] & 1) {
      print(false);
      return;
    }
  }
  for (int i = 1; i < n; ++i) {
    s += (n - i) * t[i];
  }
  print(d[0] - s > 0 && (d[0] - s) % (2 * n) == 0);
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