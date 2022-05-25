/** @file
 * @ingroup


 */
#include <bits/stdc++.h>
using namespace std;
template <typename T> inline void O(const T &x) { cout << x << '\n'; }
template <typename T, typename... W> inline void O(const T &x, const W &...b) {
  cout << x << ' ';
  O(b...);
}
template <typename T> inline void rd(T &x) { cin >> x; }
template <typename T, typename... W> inline void rd(T &x, W &...b) {
  cin >> x;
  rd(b...);
}
#ifndef MISAKA
#define err(...)
#else
#define err(...) fprintf(stderr, __VA_ARGS__)
#endif
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef long double dbl;
typedef pair<int, int> pii;
typedef uniform_int_distribution<int> r32;
typedef uniform_int_distribution<i64> r64;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define shuf(L, R) shuffle((L), (R), rng)
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define FOR(i, j, k) for (int i = (j); i <= (k); ++i)
#define ROF(i, j, k) for (int i = (k); i >= (j); --i)
template <typename T> inline void ckmin(T &a, const T &b) { a = min(a, b); }
template <typename T> inline void ckmax(T &a, const T &b) { a = max(a, b); }
//#define IOFILE "filename"
//#define MULTI
const int N = 2e5+5;

vector<int> g0[N], g[N<<1];
int n, ex;
int dfn[N], low[N], tot;
int stk[N], hd;

void tarjan(int u) {
  low[u] = dfn[u] = ++tot;
  stk[++hd] = u;
  for (auto v : g0[u]) {
    if (!dfn[v]) {
      tarjan(v);
      ckmin(low[u], dfn[v]);
      if (low[v] == dfn[u]) {
        ++ex;
        g[ex].pb(u);
        g[u].pb(ex);
        int cur = 0;
        do {
          cur = stk[hd--];
          g[ex].pb(cur);
          g[cur].pb(ex);
        } while (cur != v);
      }
    } else ckmin(low[u], low[v]);
  }
}

class O1LCA {
  static const int W = 20;
  int dis[N<<1], d[N<<1], f[W][N<<2], dfn[N], tot;
  bool ok[N<<1];
  inline void dfs(int u, int fa) {
    dfn[u] = ++tot;
    d[tot] = d[dfn[fa]]+1;
    f[0][tot] = tot;
    dis[tot] = dis[dfn[fa]] + (u <= n);
    ok[tot] = u <= n;
    for (auto v : g[u]) if (v != fa) dfs(v, u), ++tot, f[0][tot] = dfn[u];
  }
  inline int cmin(int u, int v) {
    if (d[u] < d[v]) return u;
    return v;
  }
public:
  inline void init() {
    dfs(1,0);
    FOR(i,1,ex) err("%d %d\n", dfn[i], d[i]);
    for (int i = 1; i < W; ++i) for (int j = 1; j + (1<<i) <= tot + 1; ++j) {
      f[i][j] = cmin(f[i-1][j], f[i-1][j+(1<<(i-1))]);
    }
  }
  inline int lca(int u, int v) {
    if (u > v) swap(u, v);
    int t = 31 - __builtin_clz(v - u + 1);
    return cmin(f[t][u], f[t][v - (1<<t) + 1]);
  }
  inline int operator() (int u, int v) {
    int u0 = u, v0 = v;
    u = dfn[u], v = dfn[v];
    int x = lca(u, v);
    err("dis(%d, %d) = %d %d\n", u0, v0, x, dis[u] + dis[v] - 2 * dis[x] + ok[x]);
    return dis[u] + dis[v] - 2 * dis[x] + ok[x];
  }
} dis;

int a[N];

inline void sol() {
  int m, q;
  rd(n, m, q);
  ex = n;
  FOR(i,1,m) {
    int u, v;
    rd(u, v);
    g0[u].pb(v);
    g0[v].pb(u);
  }
  tarjan(1);
  dis.init();
  while (q--) {
    int k;
    rd(k);
    FOR(i,1,k) rd(a[i]);
    i64 ans = 0;
    FOR(i,1,n) {
      i64 cur = 0;
      FOR(j,1,k) cur += n - dis(i, a[j]);
      ckmax(ans, cur);
    }
    O(ans);
  }
}

int main() {
#ifndef MISAKA
#ifdef IOFILE
  freopen(IOFILE ".in", "r", stdin);
  freopen(IOFILE ".out", "w", stdout);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
#ifdef MULTI
  int T;
  cin >> T;
  while (T--)
#endif
    sol();
  return 0;
}

