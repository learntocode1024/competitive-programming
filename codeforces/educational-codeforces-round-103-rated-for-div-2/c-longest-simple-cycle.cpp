// Original Author: misaka18931
// Date: 02-05-21
// tag: greedy
// AC

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

inline void print(const bool &b) {
  if (b) cout << "YES" << endl;
  else cout << "NO" << endl;
}

LL len[MX], num[MX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> len[i];
    --len[i];
  }
  for (int i = 0; i < n; ++i) {
    cin >> num[i];
  }
  for (int i = 0, t; i < n; ++i) {
    cin >> t;
    if (i) {
      num[i - 1] = len[i - 1] - abs(num[i] - t);
    }
  }
  num[0] = len[0] - num[0];
  num[n - 1] = len[n - 1];
  LL ans = 0, curr = 0;
  for (int i = n - 1; i > 0; --i) {
    if (num[i] == len[i]) { // end
      ans = max(ans, curr);
      curr = num[i] + 2;
    } else {
      ans = max(ans, curr + len[i] - num[i]); // force end
      curr = max(curr + num[i], len[i]) + 2;
    }
  }
  ans = max(curr + num[0], ans);
  cout << ans LF;
  for (int i = 0; i <= n + 10; ++i) {
    num[i] = len[i] = 0;
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