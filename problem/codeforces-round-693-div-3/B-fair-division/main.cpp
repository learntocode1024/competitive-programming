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

int cnt[3];

void solve() {
  cnt[1] = cnt[2] = 0;
  int n;
  cin >> n;
  int a;
  int sum = 0;
  while (n--) {
    cin >> a;
    ++cnt[a];
    sum += a;
  }
  bool ans = true;
  if (sum & 1) ans = false;
  sum >>= 1;
  if (sum & 1 && sum < 2 * cnt[2] && !cnt[1]) ans = false;
  if (ans) cout << "YES\n";
  else cout << "NO\n"; 
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
