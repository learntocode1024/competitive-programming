#include <algorithm>
#include <bitset>
#include <cctype>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

// #include "io"
#include "utils"

const int N = 200005;
vector<int> G[N];
int n, m, k;

int sz[N], son[N], dep[N], f[N], dfn[N], rnk[N], top[N], tot;
int init_op[N];
u64 init_val[N];

struct bitop {
  static const u64 mask = 0xFFFFFFFFFFFFFFFF;
  u64 v0, v1;
  bitop() : v0(0), v1(mask) {};
  bitop(u64 a, u64 b) : v0(a), v1(b) {};
  bitop operator* (const bitop &rhs) const { // combine 2 operations
    return bitop((v0 & rhs.v1) | ((~v0) & rhs.v0), (v1 & rhs.v1) | ((~v1) & rhs.v0));
  }
};
using node = pair<bitop, bitop>; // first : upwords, second : downwards
inline node p1(u64 x) {
  return {bitop(0, x), bitop(0, x)};
}
inline node p2(u64 x) {
  return {bitop(x, bitop::mask), bitop(x, bitop::mask)};
}
inline node p3(u64 x) {
  return {bitop(x, ~x), bitop(x, ~x)};
}
decltype(&p1) op[4];

struct DS {
  node a[N << 2];
  inline void up(int p) {
    a[p].fi = a[(p << 1) | 1].fi * a[p << 1].fi;
    a[p].se = a[p << 1].se * a[(p << 1) | 1].se;
  }
  void assign(int p, int l, int r, int s, const node &v) {
    if (r == l + 1) return a[p] = v, void();
    int mid = l + (r - l) / 2;
    if (s < mid) assign(p << 1, l, mid, s, v);
    else assign((p << 1) | 1, mid, r, s, v);
    up(p);
  }
  bitop upsum(int p, int l, int r, int s, int t) {
    if (l == s && r == t) return a[p].fi;
    int mid = l + (r - l) / 2;
    if (s >= mid) return upsum((p << 1) | 1, mid, r, s, t);
    if (t <= mid) return upsum(p << 1, l, mid, s, t);
    return upsum((p << 1) | 1, mid, r, mid, t) * upsum(p << 1, l, mid, s, mid);

  }
  bitop dnsum(int p, int l, int r, int s, int t) {
    if (l == s && r == t) return a[p].se;
    int mid = l + (r - l) / 2;
    if (s >= mid) return dnsum((p << 1) | 1, mid, r, s, t);
    if (t <= mid) return dnsum(p << 1, l, mid, s, t);
    return dnsum(p << 1, l, mid, s, mid) * dnsum((p << 1) | 1, mid, r, mid, t);
  }
  void build(int p, int l, int r) {
    if (r - l == 1) {
      a[p] = op[init_op[rnk[l]]](init_val[rnk[l]]);
      return;
    }
    int mid = l + (r - l) / 2;
    build(p << 1, l, mid);
    build((p << 1) | 1, mid, r);
    up(p);
  }
} T;

void dfs1(int u, int fa) {
  f[u] = fa;
  sz[u] = 1;
  dep[u] = dep[fa] + 1;
  for (auto v : G[u]) {
    if (v != fa) {
      dfs1(v, u);
      sz[u] += sz[v];
      if (sz[v] > sz[son[u]]) son[u] = v;
    }
  }
}

void dfs2(int u, int t) {
  top[u] = t;
  dfn[u] = ++tot;
  rnk[tot] = u;
  if (son[u]) dfs2(son[u], t);
  for (auto v : G[u]) {
    if (!dfn[v]) dfs2(v, v);
  }
}

bitop path(int a, int b) { // from a to b (directed)
  bitop ret1, ret2, ret3;
  while (top[a] != top[b]) {
    if (dep[top[a]] > dep[top[b]]) {
      ret1 = ret1 * T.upsum(1, 1, n + 1, dfn[top[a]], dfn[a] + 1);
      a = f[top[a]];
    } else {
      ret2 = T.dnsum(1, 1, n + 1, dfn[top[b]], dfn[b] + 1) * ret2;
      b = f[top[b]];
    }
  }
  if (dep[a] >= dep[b]) ret3 = T.upsum(1, 1, n + 1, dfn[b], dfn[a] + 1);
  else ret3 = T.dnsum(1, 1, n + 1, dfn[a], dfn[b] + 1);
  return (ret1 * ret3) * ret2;
}

inline u64 maxv(bitop a, u64 x) {
  // cerr << bitset<3>(a.v0) << ' ' << bitset<3>(a.v1) << '\n';
  u64 ret(0), cx(0);
  u64 v0 = a.v0, v1 = a.v1;
  ROF(i, 0, k) {
    if ((cx | 1ull << i) <= x
     && ((v1 >> i) & 1ull) == 1
     && ((v0 >> i) & 1ull) == 0) { // choose 1 when have to
      ret |= 1ull << i;
      cx |= 1ull << i;
    } else {
      ret |= (v0 & (1ull << i));
    }
  }
  return ret;
}

void solve() {
  int u, v, q, x, y;
  u64 z;
  cin >> n >> m >> k;
  FOR(i, 1, n + 1) {
    cin >> init_op[i] >> init_val[i];
  }
  FOR(i, 1, n) {
    cin >> u >> v;
    G[u].pb(v);
    G[v].pb(u);
  }
  dfs1(1, 0);
  dfs2(1, 1);
  T.build(1, 1, n + 1);
  FOR(i, 0, m) {
    cin >> q >> x >> y >> z;
    if (q == 2) {
      T.assign(1, 1, n + 1, dfn[x], op[y](z));
    } else {
      cout << maxv(path(x, y), z) << '\n';
    }
  }
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  op[1] = &p1;
  op[2] = &p2;
  op[3] = &p3;
  // IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--) solve();
#else
  solve();
#endif
  return 0;
}
