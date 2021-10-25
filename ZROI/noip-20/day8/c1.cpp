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

const int M = 1 << 14;
i64 A[M], B[M], pg[M];
inline int wrap(int x) { return 1 << (32 - __builtin_clz(x)); }
int bv[M];

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

inline void fft(i64* a, int len) {
  for (int i = 1; i < len; ++i) {
    bv[i] = bv[i >> 1] >> 1;
    if (i & 1) bv[i] |= len >> 1;
    if (bv[i] > i) swap(a[i], a[bv[i]]);
  }
  for (int i = 1; i < len; i <<= 1) {
    i64 w0 = pg[M / i / 2];
    for (int j = 0; j < len; j += (i << 1)) {
      i64 w = 1;
      for (int k = j; k < j + i; ++k) {
        i64 x = a[k], y = a[k + i] * w % p;
        red(a[k] = x + y);
        red(a[k + i] = x + p - y);
        w = w * w0 % p;
      }
    }
  }
}

inline void idft(i64* a, int len) {
  fft(a, len);
  reverse(a + 1, a + len);
  i64 iv = inv(len);
  FOR(i, 0, len) a[i] = a[i] * iv % p;
}

i64 AA[N], BB[N], _c[N];

void inv(i64 *a, int len) { // _c A B
  _c[0] = q_pow(a[0], p - 2);
  int lm = wrap(len);
  for (int n = 1; n < len; n <<= 1) {
    int lim = n << 2;
    FOR(i, 0, n) AA[i] = _c[i];
    FOR(i, 0, n << 1) BB[i] = a[i];
    fft(AA, lim);
    fft(BB, lim);
    FOR(i, 0, lim) AA[i] = (AA[i] * 2 + p - AA[i] * AA[i] % p * BB[i] % p) % p;
    idft(AA, lim);
    FOR(i, 0, n << 1) _c[i] = AA[i];
    FOR(i, 0, lim) AA[i] = BB[i] = 0;
  }
  for (int i = 0; i < len; ++i) a[i] = _c[i];
  for (int i = 0; i < lm; ++i) _c[i] = 0;
}

void dfs2(int u, int fa) {
  if (fa) {
    int lim = wrap(sz[u] + sz[u] + sz[fa] + 1);
    FOR(i, 0, lim) A[i] = B[i] = 0;
    FOR(i, 0, sz[u] + 1) A[i] = dp[u][i];
    FOR(i, 1, sz[fa] + 1) B[i] = dp[fa][i];
    inv(A, k + 1);
    fft(A, lim);
    fft(B, lim);
    FOR(i, 0, lim) {
      red(A[i] = p - A[i] * B[i] % p);
    }
    idft(A, lim);
    FOR(i, 2, k + 1) red(dp[u][i] += A[i]);
  }
  for (auto v : g[u]) {
    if (v == fa) continue;
    dfs2(v, u);
  }
}

inline void prework() {
  pg[0] = 1;
  i64 gg = q_pow(3, (p - 1) / M);
  FOR(i, 1, M) pg[i] = pg[i - 1] * gg % p;
}

inline void solve() {
  prework();
  cin >> n >> k;
  FOR(i, 1, n + 1) cin >> a[i];
  FOR(i, 1, n) {
    int u, v;
    cin >> u >> v;
    g[u].pb(v);
    g[v].pb(u);
  }
  dfs1(1, 0);
  dfs2(1, 0);
  FOR(i, 1, n + 1) {
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

