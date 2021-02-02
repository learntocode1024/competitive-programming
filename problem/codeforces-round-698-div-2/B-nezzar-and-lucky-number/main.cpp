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
int cnt[10];

inline void print(const bool &b) {
  if (b) cout << "YES" << endl;
  else cout << "NO" << endl;
}

void solve() {
  LL n;
  int q, r, mod;
  cin >> q >> mod;
  for (int i = 0; i < 10; ++i) {
    cnt[i] = 10;
    for (int j = 9; j >= 0; --j) {
      if ((j * mod + i) % 10 == 0) cnt[i] = j; 
    }
  }
  while (q--) {
    cin >> n;
    r = n % mod;
    print((cnt[r] < n / mod) || (cnt[r] == n / mod) && (cnt[r] == 10));
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