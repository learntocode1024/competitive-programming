// Original Author: misaka18931
// Date: 02-07-21
// tag:
// 

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define LF << '\n'
#define SPC << ' '
#define CLRBUF cout << endl;
#define MX 100005
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 1e9 + 7;

inline void print(const bool &b) {
  if (b) cout << "YES" << endl;
  else cout << "NO" << endl;
}
LL a[MX], b[MX];
void solve() {
  LL A, B, n;
  cin >> A >> B >> n;
  LL amax = 0;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    amax = max(amax, a[i]);
  }
  B += amax;
  for (int i = 0; i < n; ++i) {
    cin >> b[i];
  }
  for (int i = 0; i < n; ++i) {
    B -= (b[i] / A + 1 - (b[i] % A == 0)) * a[i];
  }
  print(B > 0);
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