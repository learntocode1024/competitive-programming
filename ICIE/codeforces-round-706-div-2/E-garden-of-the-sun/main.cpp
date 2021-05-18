// Original Author: misaka18931
// Date: 03-03-21
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
#define LF << '\n'
#define SPC << ' '
#define CLRBUF cout << endl;
#define init(T, x) \
  T x; \
  cin >> x;
#define printb(x) \
  if ((bool)x) printf("YES"); \
  else printf("NO");
#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define MX 505

int n, m;
string ch[MX];

void solve() {
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    cin >> ch[i];
  }
  int pref = (m % 3 != 1);
  for (int i = pref; i < m; i = i + 3) {
    int flag = (i >= m - 2);
    for (int j = 0; j < n; ++j) {
      ch[j][i] = 'X';
      if (!flag && ch[j][i + 1] == 'X') ch[j][i + 2] = 'X', flag = 1;
      if (!flag && ch[j][i + 2] == 'X') ch[j][i + 1] = 'X', flag = 1;
    }
    if (!flag) ch[0][i + 1] = ch[0][i + 2] = 'X';
  }
  for (int i = 0; i < n; ++i) {
    cout << ch[i] << endl;
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
