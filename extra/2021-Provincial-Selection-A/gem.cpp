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

const int N = 2e5+5, LG = 18;
vector<int> g[N];
int n, m, c, q;
int P[N], w[N], rP[N];
int ans[N];
int f[LG][N], nxt[LG][N], v1[N];
int dep[N] = {0, 1};

int lst[N];

void dfs(int u, int fa) {
  nxt[0][u] = lst[w[u] + 1];
  int mem = lst[w[u]];
  if (w[u] <= c) lst[w[u]] = u;
  v1[u] = lst[1];
  for (auto v : g[u]) if (v != fa) {
    dep[v] = dep[u] + 1;
    f[0][v] = u;
    dfs(v, u);
  }
  lst[w[u]] = mem;
}

inline int lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  int x = dep[u] - dep[v];
  FOR(i, 0, LG) if ((x >> i) & 1) u = f[i][u];
  if (u == v) return u;
  ROF(i, 0, LG) if (f[i][u] != f[i][v])
    u = f[i][u], v = f[i][v];
  return f[0][u];
}

vector<pii> tg[N];

inline void path(int u, int v, int id) {
  int x = lca(u, v);
  int up = 0;
  if (dep[v1[u]] >= dep[x]) ++up;
  u = v1[u];
  ROF(i, 0, LG) 
    if (dep[nxt[i][u]] >= dep[x]) 
      u = nxt[i][u], up += 1 << i;
  if (x == v) ans[id] = up;
  else {
    tg[x].eb(id, up);
    tg[v].eb(id, -1);
  }
}

const int MX = N * 3;
namespace T {
  int id_c[MX], f[MX], tot;
  int sz[MX], vl[MX];
  void init() {
    FOR(i, 0, c + 1) id_c[i] = q + 1 + i, f[q + 1 + i] = q + 1 + i, vl[q + 1 + i] = i, sz[q + 1 + i] = 1;
    tot = q + c + 1;
  }
  int get(int u) {
    if (u == f[u]) return u;
    return get(f[u]);
  }
  struct his { // f sz id_c vl
    int a, aa, b, bb, c, cc, d, dd, e, ee;
    inline void set() {
      f[a] = aa;
      sz[b] = bb;
      id_c[c] = cc;
      if (d >= 0)vl[d] = dd;
      if (e >= 0)id_c[e] = ee;
    }
  } H[MX];
  int th;
  void merge(int c) {
    int u = get(id_c[c - 1]), v = get(id_c[c]);
    if (sz[u] < sz[v]) { // v <- u
      H[th] = {u, f[u], v, sz[v], c - 1, id_c[c - 1], -1, 0, -1, 0};
      f[u] = v;
      sz[v] += sz[u];
      id_c[c - 1] = ++tot;
      f[tot] = tot; //
      vl[tot] = c - 1; //
      sz[tot] = 1; //
    } else { // u <- v
      H[th] = {v, f[v], u, sz[u], c, id_c[c], u, vl[u], c - 1, id_c[c - 1]};
      f[v] = u;
      sz[u] += sz[v];
      vl[u] = c;
      id_c[c] = u;
      id_c[c - 1] = ++tot;
      f[tot] = tot; //
      vl[tot] = c - 1; //
      sz[tot] = 1; //
    }
    ++th;
  }
  inline void mount(int id, int c) {
    f[id] = id_c[c];
  }
  inline int extract(int id) {
    return vl[get(id)];
  }
  inline void yike() {
    H[th-1].set();
    --th;
  }
};

void calc(int u, int fa) {
  for (auto v : tg[u]) {
    if (v.se != -1) T::mount(v.fi, v.se);
  }
  if (w[u] <= c) T::merge(w[u]);
  for (auto v : tg[u]) {
    if (v.se == -1) ans[v.fi] = T::extract(v.fi);
  }
  for (auto v : g[u]) if (v != fa) calc(v, u);
  T::yike();
}

inline void solve() {
  rd(n, m, c);
  FOR(i, 1, c + 1) rd(P[i]);
  FOR(i, 1, n + 1) rd(w[i]);
  FOR(i, 1, m + 1) rP[i] = m;
  FOR(i, 1, c + 1) rP[P[i]] = i;
  FOR(i, 1, n + 1) w[i] = rP[w[i]]; // P -> [1, c]
  FOR(i, 1, n) {
    int u, v;
    rd(u, v);
    g[u].pb(v);
    g[v].pb(u);
  }
  dfs(1, 0);
  FOR(i, 1, LG) FOR(j, 1, n + 1) {
    f[i][j] = f[i-1][f[i-1][j]];
    nxt[i][j] = nxt[i-1][nxt[i-1][j]];
  }
  cin >> q;
  FOR(i, 0, q) {
    int u, v;
    rd(u, v);
    path(u, v, i + 1); // up && tag
  }
  T::init();
  calc(1, 0); // down
  FOR(i, 0, q) println(ans[i + 1]);
}

int main() {
#ifndef MISAKA
  // freopen("gem2.in", "r", stdin);
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

