#include <algorithm>
#include <iostream>
#include <vector>

#include "utils"
#include "io"

char s[20], cs[20];
int cnt[10];
int p[10], q[10];

void solve() {
  FOR(i, 0, 10) cnt[i] = p[i] = q[i] = 0;
  FOR(i, 0, 20) s[i] = cs[i] = 0;
  int n = IO::rdstr(s) - s, k = rd();
  FOR(i, 0, n) s[i] -= '0';
  int m = 0;
  i64 ans = 2000000000ll;
  FOR(i, 0, n) {
    if (!cnt[s[i]]) p[m] = s[i], ++m;
    ++cnt[s[i]];
  }
  if (m <= k) {
    for (int i = 0; i < n; ++i) s[i] += '0';
    cout << s << '\n';
    return;
  }
  int _k = k;
  for (int i = 1; i < (1 << m); ++i) {
    if (__builtin_popcount(i) > _k) continue;
    int tot = 0;
    for (int j = 0; j < m; ++j) {
      if (i & (1 << j)) q[tot++] = p[j];
    }
    k = tot;
    sort(q, q + k);
    int _cnt = -1;
    while (s[_cnt + 1] == q[k - 1]) ++_cnt; 
    if (s[_cnt + 1] > q[k - 1]) continue;
    for (int j = 0; j < n; ++j) {
      if (s[j] <= q[k - 1]) cs[j] = s[j];
      else {
        while (cs[j - 1] == q[k - 1]) --j;
        ++ cs[j - 1];
        for (; j < n; ++j) cs[j] = 0;
        break;
      }
    }
    for (int j = 0; j < n; ++j) {
      int t = *lower_bound(q, q + k, cs[j]);
      if (t > cs[j]) {
        cs[j] = t;
        ++j;
        for (; j < n; ++j) cs[j] = q[0];
        break;
      }
    }
    i64 cur = 0;
    for (int j = 0; j < n; ++j) {
      cur = cur * 10 + cs[j];
    }
    chkmin(ans, cur);
  }
  cout << ans << '\n';
}

int main() {
  IO::init_in();
  int t = rd();
  while (t--) {
    solve();
  }
  return 0;
}