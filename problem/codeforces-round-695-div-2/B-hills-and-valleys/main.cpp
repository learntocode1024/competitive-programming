// Original Author: misaka18931
// Date: 01-08-21
// tag:
// 

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define LF << '\n'
#define SPC << ' '
#define CLRBUF cout << endl;
#define MX 300005
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 1e9 + 7;

inline void print(const bool &b) {
  if (b) cout << "YES" << endl;
  else cout << "NO" << endl;
}

int a[MX];
bool v[MX], h[MX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  int cnt = 0;
  for (int i = 1; i < n - 1; ++i) {
    if (a[i - 1] > a[i] && a[i + 1] > a[i]) v[i] = 1, ++cnt;
    if (a[i - 1] < a[i] && a[i + 1] < a[i]) h[i] = 1, ++cnt;
  }
  int p = 0;
  for (int i = 1; i < n - 1; ++i) {
    if (h[i]) {
      if (v[i - 1] && v[i + 1]) p = max(p, 3);
      else if (v[i - 1] && a[i + 1] == a[i + 2]) p = max(p, 2);

    } else if (v[i]) {

    } else {

    }
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
