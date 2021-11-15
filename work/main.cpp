#include <bits/stdc++.h>
using namespace std;
template<typename T>
void rd(T &a) {
  cin >> a;
}
template<typename A, typename... B>
void rd(A &a, B& ...b) {
  cin >> a;
  rd(b...);
}
template<typename A>
void print(const A& a) {
  cout << a;
}
template<typename A, typename... B>
void print(const A& a, const B& ...b) {
  cout << a;
  print(b...);
}
template<typename A>
void println(const A& a) {
  cout << a << '\n';
}
template<typename A, typename... B>
void println(const A& a, const B& ...b) {
  cout << a << ' ';
  println(b...);
}
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

const int N = 2e5+5;
const int p = 998244353;
i64 pw[N<<1] = {1, p / 2 + 1};
i64 fac[N << 1], ifac[N << 1], inv[N << 1];

void work() {
  fac[0] = fac[1] = ifac[0] = ifac[1] = inv[1] = 1ll;
  for (int i = 2; i < N << 1; ++i) {
    pw[i] = pw[i - 1] * pw[1] % p;
    inv[i] = (p - p / i) * inv[p % i] % p;
    fac[i] = fac[i - 1] * i % p;
    ifac[i] = ifac[i - 1] * inv[i] % p;
  }
}

inline i64 C(int n, int k) {
  if (k > n || k < 0) return 0;
  return fac[n] * ifac[k] % p * ifac[n - k] % p;
}

int d[N], fa[20][N];
int n;
vector<int> g[N];
void dfs(int u, int fa) {
  ::fa[0][u] = fa;
  for (auto v : g[u]) {
    if (v == fa) continue;
    d[v] = d[u] + 1;
    dfs(v, u);
  }
}


void lca_init() {
  dfs(1, 0);
  for (int i = 1; i < 32 - __builtin_clz(n); ++i) {
    for (int j = 1; j <= n; ++j) {
      fa[i][j] = fa[i - 1][fa[i - 1][j]];
    }
  }
}

int lca(int u, int v) {
  if (d[u] < d[v]) swap(u, v);
  int x = d[u] - d[v];
  for (int i = 20; i >= 0; --i) {
    if ((x >> i) & 1) u = fa[i][u];
  }
  if (u == v) return u;
  for (int i = 20; i >= 0; --i) {
    if (fa[i][u] != fa[i][v]) u = fa[i][u], v = fa[i][v];
  }
  return fa[0][u];
}
inline void solve() {
  work();
  n;
  cin >> n;
  FOR(i, 1, n) {
    int u, v;
    rd(u, v);
    g[u].pb(v);
    g[v].pb(u);
  }
  lca_init();
  int q;
  rd(q);
  FOR(i, 0, q) {
    int u, v;
    rd(u, v);
    int x = lca(u, v);
    cout << pw[d[u] + d[v] - d[x]*2] * C(d[u] + d[v] - d[x]*2, d[u] - d[x]) % p << '\n';
  }
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

