// Original Author: misaka18931
// Date: 03-17-21
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
#define MX 105

int cnt[MX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < 101; ++i) {
    cnt[i] = 0;
  }
  for (int i = 0; i < n; ++i) {
    int t;
    cin >> t;
    ++cnt[t];
  }
  for (int i = 0; i <= 100; ++i) {
    if (cnt[i]) {
      --cnt[i];
      cout << i << ' ';
    }
  }
  for (int i = 100; i >= 0; --i) {
    while (cnt[i]--) {
      cout << i << ' ';
    }
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
