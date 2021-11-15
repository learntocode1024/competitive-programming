#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef pair<int, int> pii;
#define mkp make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define FOR(i, j, k) for (int i = (j); i < (k); ++i)
#define ROF(i, j, k) for (int i = ((k) - 1); i >= j; --i)
template<typename T>
inline void chkmin(T &a, const T b) {
  a = min(a, b);
}
template<typename T>
inline void chkmax(T &a, const T b) {
  a = max(a, b);
}

const int N = 1e5+5, M = 3e5+5;
const int p = 998244353;
inline void red(int &x) { if (x >= p) x -= p; }
int all;
int dif[M];
int n, m;

struct sam {
  int tot;
  int lst;
  int f[M];
  int len[M];
  map<int, int> nxt[M];
  inline void expand(int c) {
    int cur = ++tot;
    len[cur] = len[lst] + 1;
    int p = lst;
    for (; p != -1 and nxt[p].find(c) == nxt[p].end(); p = f[p])
      nxt[p][c] = cur;
    if (p == -1) {
      f[cur] = 0;
    } else {
      int q = nxt[p][c];
      if (len[q] == len[p] + 1) {
        f[cur] = q;
      } else {
        int mir = ++tot;
        nxt[mir] = nxt[q];
        f[mir] = f[q];
        len[mir] = len[p] + 1;
        f[cur] = f[q] = mir;
        for (; p != -1 and nxt[p][c] == q; p = f[p])
          nxt[p][c] = mir;
      }
    }
    lst = cur;
  }
  int dp[M];
  int ord[M], buc[M];
  inline void init() {
    FOR(i, 0, tot + 1) ord[i] = dp[i] = f[i] = len[i] = 0, nxt[i].clear();
    tot = 0;
    f[0] = -1;
    tot = lst = 0;
    int n, c;
    cin >> n;
    FOR(i, 0, n + 1) buc[i] = 0;
    FOR(i, 0, n) cin >> c, expand(c);
  }
  inline void run() {
    for (auto v : nxt[0]) {
      red(dp[v.se] = all + p - dif[v.fi]);
      dif[v.fi] = all;
    }
    int mlen = 0;
    for (int i = 1; i <= tot; ++i) {
      ++buc[len[i]];
      chkmax(mlen, len[i]);
    }
    FOR(i, 1, mlen + 1) buc[i] += buc[i - 1];
    FOR(i, 1, tot + 1) ord[buc[len[i]]--] = i;
    FOR(i, 1, tot + 1) {
      int u = ord[i];
      red(all += dp[u]);
      for (auto v : nxt[u]) {
        red(dif[v.fi] += dp[u]);
        red(dp[v.se] += dp[u]);
      }
    }
  }
} S;

inline void solve() {
  all = 1;
  cin >> n >> m;
  FOR(i, 0, n) S.init(), S.run();
  int ans = 0;
  FOR(i, 1, m + 1) red(ans += all), red(ans += p - dif[i]);
  red(ans += p - m);
  cout << all - 1 << '\n';
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
  solve();
  return 0;
}
/* Checklist:
 * - data type
 * - overflow
 * - typo/logic
 * - special cases
 * - cleanup (multi-test)
 * - bounds
 * - memory usage
 * - file IO
 */
