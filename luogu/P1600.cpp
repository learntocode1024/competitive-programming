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

const int N = 3e5+5;
int U[N<<1], D[N<<2], d[N], w[N], ans[N];
vector<int> g[N], uu[N], dd[N];
int f[19][N];
int n, m;

void dfs(int u, int fa) {
  f[0][u] =fa;
  for (auto v : g[u]) {
    if (v != fa) {
      d[v] = d[u] + 1;
      dfs(v, u);
    }
  }
}

inline int lca(int u, int v) {
  if (d[u] < d[v]) swap(u, v);
  int x = d[u] - d[v];
  ROF(i, 0, 19) if ((x >> i) & 1) u = f[i][u];
  if (u == v) return u;
  ROF(i, 0, 19) if (f[i][u] != f[i][v])
    u = f[i][u], v = f[i][v];
  return f[0][u];
}

inline int l2(int u, int x) {
  int t = d[u] - d[x] - 1;
  ROF(i, 0, 19) if ((t >> i) & 1) u = f[i][u];
  return u;
}

void calc(int u, int fa) {
  for (auto i : uu[u]) {
    if (i > 0) ++U[i];
  }
  for (auto i : dd[u]) {
    if (i > 0) ++D[i];
  }
  ans[u] = U[w[u]+d[u]+1] + D[N+d[u]-w[u]];
  for (auto i : uu[u]) {
    if (i < 0) --U[-i];
  }
  for (auto i : dd[u]) {
    if (i < 0) --D[-i];
  }
  for (auto v : g[u])
    if (v != fa) calc(v, u);

  for (auto i : uu[u]) {
    if (i > 0) --U[i];
    else ++U[-i];
  }
  for (auto i : dd[u]) {
    if (i > 0) --D[i];
    else ++D[-i];
  }
}

inline void solve() {
  cin >> n >> m;
  FOR(i, 1, n) {
    int u, v;
    cin >> u >> v;
    g[u].pb(v);
    g[v].pb(u);
  }
  dfs(1, 0);
  FOR(i, 1, 19) FOR(j, 1, n + 1) {
    f[i][j] = f[i-1][f[i-1][j]];
  }
  FOR(i, 1, n + 1) cin >> w[i];
  FOR(i, 0, m) {
    int s, t;
    cin >> s >> t;
    if (t == 2) {
      cerr << "\n";
    }
    int x = lca(s, t);
    uu[x].pb(d[s]+1);
    uu[s].pb(-d[s]-1);
    if (t != x) {
      dd[l2(t, x)].pb(N+d[x]+d[x]-d[s]);
      dd[t].pb(-N-d[x]-d[x]+d[s]);
    }
  }
  calc(1, 0);
  FOR(i, 1, n + 1) cout << ans[i] << " \n"[i==n];
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

