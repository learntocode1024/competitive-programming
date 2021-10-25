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

const int N = 3005;
const int p = 998244353;
inline void red(i64 &x) { if (x >= p) x -= p; }
i64 dp[N][N];
int n, k;
i64 a[N];
vector<int> g[N];
int sz[N];
i64 h[N], t[N], tt[N];

void dfs1(int u, int fa) {
  dp[u][1] = a[u];
  sz[u] = 1;
  for (auto v : g[u]) {
    if (v == fa) continue;
    dfs1(v, u);
    FOR(i, 0, min(sz[u], k) + 1) h[i] = dp[u][i], dp[u][i] = 0;
    FOR(i, 1, min(sz[u], k) + 1) {
      FOR(j, 0, min(sz[v], k) + 1) {
        if (i + j <= k) red(dp[u][i + j] += h[i] * dp[v][j] % p);
      }
    }
    sz[u] += sz[v];
  }
  dp[u][0] = 1;
}

void dfs2(int u, int fa) {
  if (fa) {
    FOR(i, 0, k + 1) t[i] = h[i] = tt[i] = 0;
    FOR(i, 1, min(k, sz[u]) + 1) {
      FOR(j, 1, min(k, sz[u] + 1)) {
        if (i + j > k) break;
        red(t[i + j] += dp[u][i] * dp[u][j] % p);
      }
    }
    FOR(i, 1, k + 1) {
      FOR(j, 1, k + 1) {
        if (i + j > k) break;
        red(tt[i + j] += t[i] * dp[fa][j] % p);
      }
    }
    FOR(i, 1, k + 1) {
      FOR(j, 1, k + 1) {
        if (i + j > k) break;
        red(h[i + j] += dp[u][i] * dp[fa][j] % p);
      }
    }
    FOR(i, 1, k + 1) red(dp[u][i] += (h[i] + p - tt[i]) % p), cerr << h[i] << ' ' << tt[i] << " | ";
    cerr << '\n';
  }
  for (auto v : g[u]) {
    if (v == fa) continue;
    dfs2(v, u);
  }
}
inline void solve() {
  cin >> n >> k;
  FOR(i, 1, n + 1) cin >> a[i];
  FOR(i, 1, n) {
    int u, v;
    cin >> u >> v;
    g[u].pb(v);
    g[v].pb(u);
  }
  // dfs2(1, 0);
  FOR(i, 1, n + 1) {
    FOR(i, 1, n + 1) FOR(j, 0, k + 1) dp[i][j] = 0;
    dfs1(i, 0);
    i64 ans = 0;
    FOR(j, 1, k + 1) {
      red(ans += dp[i][j]);
    }
    cout << ans << ' ';
  }
  cout << '\n';
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

