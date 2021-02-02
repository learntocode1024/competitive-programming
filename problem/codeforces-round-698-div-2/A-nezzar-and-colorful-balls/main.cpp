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
#define MX
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 1e9 + 7;

inline void print(const bool &b) {
  if (b) cout << "YES" << endl;
  else cout << "NO" << endl;
}

void solve() {
  int n;
  cin >> n;
  int ans = 0;
  int cnt = 0;
  int num, prev = 0;
  while (n--) {
    cin >> num;
    if (num == prev) ++cnt;
    else cnt = 1, prev = num;
    ans = max(ans, cnt);
  }
  cout << ans LF;
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