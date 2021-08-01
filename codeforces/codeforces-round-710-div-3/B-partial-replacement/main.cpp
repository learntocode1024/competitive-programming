// Original Author: misaka18931
// Date: 03-18-21
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
#define MX 55

int ans[MX], pos[MX];

void solve() {
  int n, k;
  cin >> n >> k;
  char ch;
  int tot = -1;
  for (int i = 0; i < n; ++i) {
    cin >> ch;
    if (ch == '*') pos[++tot] = i;
  }
  ans[0] = 1;
  for (int i = 1; i <= tot; ++i) {
    ans[i] = 500;
    for (int j = i - 1; j >= 0 && pos[i] - pos[j] <= k; --j) {
      ans[i] = min(ans[j] + 1, ans[i]);
    }
  }
  cout << ans[tot] << endl;
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
