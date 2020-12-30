// $FILEDIR
// Author: $USERNAME
// Date: $DATE
// URL: $PROBLEMURL
// tag:
// 

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <utility>
#define MX 200005
using std::cin;
using std::cout;
using std::endl;
using std::memset;
typedef long long LL;
typedef unsigned long long ULL;
const int mod = 1e9 + 7;

int cnt[MX];
std::pair<LL, int> val[MX];

inline bool cmp(std::pair<LL, int> a, std::pair<LL, int> b) {
  return a.first > b.first;
}

    void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> val[i].first;
    val[i].second = i;
  }
  for (int i = 1; i < n; ++i) {
    int a, b;
    cin >> a >> b;
    ++cnt[a];++cnt[b];
  }
  LL ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans += val[i].first;
    --cnt[i];
  }
  cout << ans << " ";
  std::sort(val + 1, val + n + 1, cmp);
  int it = 1;
  for (int i = 2; i < n; ++i) {
    while (cnt[val[it].second] == 0) ++it;
    --cnt[val[it].second];
    ans += val[it].first;
    cout << ans << " ";
  }
  cout << endl;
  for (int i = 1; i <= n; ++i) {
    val[i] = std::make_pair(0, 0);
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
