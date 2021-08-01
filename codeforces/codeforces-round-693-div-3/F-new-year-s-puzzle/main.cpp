// Original Author: misaka18931
// Date: 01-04-21
// tag:
// 

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define MX
using std::cin;
using std::cout;
using std::endl;
using std::memset;
typedef long long LL;
typedef unsigned long long ULL;
const int mod = 1e9 + 7;

int cnt[2];

struct tmp {
  int a;
  int b;
} mem[200005];

void cmp(const tmp &a, const tmp &b) {
  
}

void solve() {
  int n, m;
  cnt[0] = cnt[1] = 0;
  cin >> n >> m;
  int a, b;
  int ans = true;
  if (m & 1) ans = false;
  for (int i = 0; i < m; ++i) {
    cin >> mem[i].a >> mem[i].b;
  }
  int tot = -1;
  while (ans && m--) {
    a = mem[++tot].a;
    b = mem[tot].b;
    --a;
    ++cnt[(b & 1) ^ a];
    if (std::abs(cnt[1] - cnt[0]) > 1) {
      ans = false;
      break;
    }
  }
  if (ans && cnt[0] == cnt[1]) cout << "YES\n";
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
