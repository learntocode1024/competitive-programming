// $FILEDIR
// Author: $USERNAME
// Date: $DATE
// URL: $PROBLEMURL
// tag:
// 

#include <cstdio>
#include <cstring>
#include <iostream>
#define MX 100005
using std::cin;
using std::cout;
using std::endl;
using std::memset;
typedef long long LL;
typedef unsigned long long ULL;
const int mod = 1e9 + 7;

int cnt[MX * 2];

void solve() {
  int n;
  cin >> n;
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    int tmp;
    cin >> tmp;
    if (cnt[tmp] == 0) ++ans;
    ++cnt[tmp];
  }
  bool extra = false;
  for (int i = 1; i <= n * 2 + 1; ++i) {
    if (cnt[i] > 1) extra = true;
    if (cnt[i] == 0 && extra) extra = false, ++ans;
  }
  cout << ans << endl;
  for (int i = 0; i <= n * 2; ++i) {
    cnt[i] = 0;
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
