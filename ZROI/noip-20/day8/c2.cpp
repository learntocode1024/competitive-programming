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
i64 dp[N], f[N][N];
int n, k;
i64 a[N];
vector<int> g[N];
int sz[N];
i64 h[N], t[N], tt[N];
int z;
inline i64 q_pow(i64 x, int a) {
  i64 ret = 1;
  while (a) {
    if (a & 1) ret = ret * x % p;
    x = x * x % p;
    a >>= 1;
  }
  return ret;
}

inline i64 inv(i64 x) { return q_pow(x, p - 2); }

void dfs1(int u, int fa) {
  dp[u] = z * a[u] % p;
  sz[u] = 1;
  for (auto v : g[u]) {
    if (v == fa) continue;
    dfs1(v, u);
    dp[u] = dp[u] * (1 + dp[v]) % p;
  }
}

void dfs2(int u, int fa) {
  if (fa) {
    dp[u] = dp[u] * (1 + dp[fa] * inv(dp[u] + 1) % p) % p;
  }
  for (auto v : g[u]) {
    if (v == fa) continue;
    dfs2(v, u);
  }
}

i64 a0[N], G[N][N], c[N];
i64 ifac[N], iv[N];

void prework() {
  a0[0] = 1;
  for (int i = 1; i <= n + 1; ++i) {
    for (int j = i; j >= 0; --j) {
      red(a0[j] = p - i * a0[j] % p);
      if (j) red(a0[j] += a0[j - 1]);
    }
  }
  for (int i = 1; i <= n + 1; ++i) {
    i64 rem = 1;
    for (int j = n; j >= 0; --j) {
      G[i][j] = rem;
      red(rem = a0[j] + i * rem % p);
    }
  }
  iv[1] = ifac[0] = ifac[1] = 1;
  FOR(i, 2, n + 1) iv[i] = (p - iv[p % i]) * (p / i) % p, ifac[i] = ifac[i - 1] * iv[i] % p;
  FOR(i, 1, n + 2) {
    FOR(j, 1, k + 1) red(c[i] += G[i][j]);
    c[i] = c[i] * ifac[i - 1] % p;
    if ((n + 1 - i) & 1) c[i] = c[i] * (p - ifac[n + 1 - i]) % p;
    else c[i] = c[i] * ifac[n + 1 - i] % p;
  }
}

inline int calc(i64 *y) {
  i64 ans = 0;
  FOR(i, 1, n + 2) {
    red(ans += y[i] * c[i] % p);
  }
  return ans;
}

inline void solve() {
  cin >> n >> k;
  prework();
  FOR(i, 1, n + 1) cin >> a[i];
  FOR(i, 1, n) {
    int u, v;
    cin >> u >> v;
    g[u].pb(v);
    g[v].pb(u);
  }
  for (z = 1; z <= n + 1; ++z) {
    dfs1(1, 0);
    dfs2(1, 0);
    FOR(i, 1, n + 1) f[i][z] = dp[i], dp[i] = 0;
  }
  FOR(i, 1, n + 1) {
    cout << calc(f[i]) << ' ';
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

