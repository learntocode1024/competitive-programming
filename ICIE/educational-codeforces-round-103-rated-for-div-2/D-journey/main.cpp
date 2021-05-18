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
#define MX 300005
using namespace std;
typedef long long LL;

inline void print(const bool &b) {
  if (b) cout << "YES" << endl;
  else cout << "NO" << endl;
}

int l[MX], r[MX];

string s;
void solve() {
  int n;
  cin >> n >> s;
  l[1] = (s[0] == 'L') ? 1 : 0;
  for (int i = 2; i <= n; ++i) {
    l[i] = (s[i - 1] == 'L')? l[i - 2] + 2: 0;
    if (s[i - 2] == 'L' && l[i]) l[i] = 1;
  }
  r[n] = 0;
  r[n - 1] = (s[n - 1] == 'R') ? 1 : 0;
  for (int i = n - 2; i >= 0; --i) {
    r[i] = (s[i] == 'R')? r[i + 2] + 2 : 0;
    if (s[i + 1] == 'R' && r[i]) r[i] = 1;
  }
  for (int i = 0; i <= n; ++i) {
    cout << l[i] + r[i] + 1 SPC;
  }
  CLRBUF
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