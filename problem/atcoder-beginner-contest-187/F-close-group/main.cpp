// Original Author: misaka18931
// Date: 01-02-21
// tag: dp(binary-compress)
// 

#include <cstdio>
#include <cstring>
#include <iostream>
#define MX 20
using std::cin;
using std::cout;
using std::endl;
using std::memset;
typedef long long LL;
typedef unsigned long long ULL;

int n, m;
bool G[MX][MX];
struct status_t {
  int cnt[MX];
  int num[MX];
  int val = __INT32_MAX__;
} dp[1 << 18];
int tmp[20];

const status_t& min(const status_t &a, const status_t& b) {
  if (a.val > b.val) return b;
  return a;
}

void conv(unsigned stat) {
  for (int i = 0; i < n; ++i) {
    if (stat & (1 << i)) {
      const unsigned id = stat - (1 << i);
      const status_t& prev = dp[id];
      int j;
      for (j = 0; j < n; ++j) {
        if (id & (1 << j) && G[i][j]) {
          ++tmp[prev.num[j]];
          if (prev.cnt[prev.num[j]] && tmp[prev.num[j]] == prev.cnt[prev.num[j]])
            break;
        }
      }
      status_t curr = prev;
      if (prev.cnt[prev.num[j]] && tmp[prev.num[j]] == prev.cnt[prev.num[j]]) {
        curr.num[i] = prev.num[j];
        ++curr.cnt[prev.num[j]];
      } else {
        ++curr.val;
        curr.num[i] = curr.val;
        ++curr.cnt[curr.val];
      }
      dp[stat] = min(dp[stat], curr);
    } // calc
  }
}

void solve() {
  cin >> n >> m;
  if (m == 0) {
    cout << n << endl;
    return;
  }
  for (int i = 0, a, b; i < m; ++i) {
    cin >> a >> b;
    --a, --b;
    G[a][b] = G[b][a] = true;
  }
  memset(dp, 0, sizeof(dp[0]));
  for (int stat = 1; stat < (1 << n); ++stat) {
    conv(stat);
  }
  cout << dp[(1 << n) - 1].val << endl;
}

int main() {
  cin.tie(NULL);
  std::ios::sync_with_stdio(false);
  int T = 1;
  // cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
