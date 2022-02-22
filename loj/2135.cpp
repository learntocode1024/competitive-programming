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

//#define MULTI
const int N = 1e5+5, W = 18;
vector<pii> g[N], G[N];
int n;
int dfn[N], ff[N], siz[N], c[N], t2;
inline int get(int x) {
  if (!x) return 0;
  int ret = 0;
  for (; x; x -= x & -x) ret += c[x];
  return ret;
}
inline void add(int x, int v) {
  for (; x <= n; x += x & -x) c[x] += v;
}

inline bool sd(int u, int v) {
  if (ff[u] == v) {
    return get(n) > 2 * (get(dfn[u]+siz[u]-1)-get(dfn[u]-1));
  } else {
    return get(n) < 2 * (get(dfn[v]+siz[v]-1)-get(dfn[v]-1));
  }
}

struct O1LCA {
  int e[W][N<<1];
  int rk[N<<1], pos[N], d[N], tot;
  void dfs(int u, int fa) {
    dfn[u] = ++t2;//
    siz[u] = 1;//
    ff[u] = fa;//
    pos[u] = ++tot;
    rk[tot] = u;
    e[0][tot] = tot;
    for (auto v : g[u]) if (v.fi != fa) {
      d[v.fi] = d[u] + v.se;
      dfs(v.fi, u);
      e[0][++tot] = pos[u];
      siz[u] += siz[v.fi];//
    }
  }
  inline void build() {
    dfs(1, 0);
    FOR(i, 1, W) {
      FOR(j, 1, tot + 1 - (1<<i)) {
        e[i][j] = min(e[i-1][j], e[i-1][j+(1<<(i-1))]);
      }
    }
  }
  inline int lca(int u, int v) {
    u = pos[u], v = pos[v];
    if (u > v) swap(u, v);
    int t = 31 - __builtin_clz(v - u + 1);
    int x = min(e[t][u], e[t][v-(1<<t)+1]);
    return rk[x];
  }
  inline int operator() (int u, int v) {
    return d[u] + d[v] - 2*d[lca(u, v)];
  }
} dist;

int sz[N], rt;
bool vis[N];

int centroid(int u, int fa) {
  sz[u] = 1;
  bool ok = 1;
  int ret = 0;
  for (auto v : g[u]) if (v.fi != fa && !vis[v.fi]) {
    ret |= centroid(v.fi, u);
    sz[u] += sz[v.fi];
    if (sz[v.fi] > sz[0]/2) ok = 0;
  }
  if ((sz[0] - sz[u]) > sz[0]/2) ok = 0;
  return ok ? u : ret;
}

int f[N];

void build(int u) {
  centroid(u, u);
  vis[u] = 1;
  for (auto v : g[u]) if (!vis[v.fi]) {
    sz[0] = sz[v.fi];
    int to = centroid(v.fi, u);
    f[to] = u;
    G[u].eb(v.fi, to);
    build(to);
  }
}

i64 s[N], sf[N], gg[N];

inline void modify(int x, int V) {
  add(dfn[x], V);
  for (int u = x; u; u = f[u]) {
    s[u] += 1ll * dist(u, x) * V;
    if (f[u]) sf[u] += 1ll * dist(f[u], x) * V;
    gg[u] += V;
  }
}

inline void calc() {
  int u = rt, lst;
  do {
    lst = u;
    for (auto v : G[u]) if (sd(u, v.fi)) {
      u = v.se;
      break;
    }
  } while (lst != u);
  i64 ans = 0;
  int ch = u;
  for (; u; u = f[u]) {
    ans += s[u] - sf[u];
    ans += 1ll * dist(ch, u) * gg[u];
    if (f[u]) ans -= 1ll * dist(ch, f[u]) * gg[u];
  }
  println(ans);
}

inline void solve() {
  int q;
  rd(n, q);
  FOR(i, 1, n) {
    int u, v, w;
    rd(u, v, w);
    g[u].eb(v, w);
    g[v].eb(u, w);
  }
  dist.build();
  sz[0] = n;
  rt = centroid(1, 0);
  build(rt);
  while (q--) {
    int u, e;
    rd(u, e);
    modify(u, e);
    calc();
  }
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
#ifdef MULTI
  int T;
  cin >> T;
  while (T--)
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
