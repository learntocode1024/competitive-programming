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
const int N = 2e5+5;
vector<int> g[N];
int n;

struct sgT {
  struct node {
    int mn, cnt;
    int tg;
  } a[N<<2];
  inline void down(int p) {
    int &tg = a[p].tg;
    a[p<<1].mn += tg;
    a[p<<1].tg += tg;
    a[p<<1|1].mn += tg;
    a[p<<1|1].tg += tg;
    tg = 0;
  }
  inline void up(int p) {
    a[p].mn = min(a[p<<1].mn, a[p<<1|1].mn);
    a[p].cnt = 0;
    if (a[p<<1].mn == a[p].mn) a[p].cnt += a[p<<1].cnt;
    if (a[p<<1|1].mn == a[p].mn) a[p].cnt += a[p<<1|1].cnt;
  }
  void ch(int p, int l, int r, int s, int t, int w) {
    if (l == s && r == t) {
      a[p].mn += w;
      a[p].tg += w;
      return;
    }
    int mid = (l + r) >> 1;
    down(p);
    if (s < mid) ch(p<<1, l, mid, s, min(mid, t), w);
    if (t > mid) ch(p<<1|1, mid, r, max(s, mid), t, w);
    up(p);
  }
  inline int get() {
    if (a[1].mn) return 0;
    return a[1].cnt;
  }
  void build(int p = 1, int l = 1, int r = n + 1) {
    if (r - l == 1) {
      a[p].cnt = 1;
      return;
    }
    int mid = (l + r) >> 1;
    build(p<<1, l, mid);
    build(p<<1|1, mid, r);
    up(p);
  }
} T;

int sz[N], son[N], dfn[N], rnk[N], f[N], hd[N], dep[N], tot;

void gson(int u, int fa) {
  sz[u] = 1;
  dep[u] = dep[fa] + 1;
  f[u] = fa;
  for (auto v : g[u]) if (v != fa) {
    gson(v, u);
    sz[u] += sz[v];
    if (sz[v] > sz[son[u]]) son[u] = v;
  }
}

void hld(int u, int fa) {
  dfn[u] = ++tot;
  rnk[tot] = u;
  if (son[u]) hd[son[u]] = hd[u], hld(son[u], u);
  for (auto v : g[u]) if (v != fa && v != son[u]) {
    hd[v] = v;
    hld(v, u);
  }
}
int sub;
inline bool anc(int u, int v) {
  int lst = u;
  swap(u, v);
  while (dep[hd[u]] > dep[hd[v]]) {
    lst = hd[u];
    u = f[hd[u]];
  }
  if (hd[u] != hd[v] || dep[u] < dep[v]) return false;
  if (u == v) sub = lst;
  else sub = rnk[dfn[v]+1];
  return true;
}

inline void add(int u, int w) {
  T.ch(1, 1, n + 1, dfn[u], dfn[u] + sz[u], w);
}

inline void path(int u, int v, int w) {
  if (dep[u] > dep[v]) swap(u, v);
  if (anc(u, v)) {
    add(sub, w);
    add(v, -w);
  } else {
    add(1, w);
    add(u, -w);
    add(v, -w);
  }
}

set<pii> S;

inline void solve() {
  int q;
  cin >> n >> q;
  T.build();
  FOR(i, 1, n) {
    int u, v;
    rd(u, v);
    g[u].pb(v);
    g[v].pb(u);
  }
  gson(1, 0);
  hd[1] = 1;
  hld(1, 0);
  FOR(i, 0, q) {
    int u, v;
    rd(u, v);
    if (u > v) swap(u, v);
    if (S.find({u, v}) != S.end()) S.erase({u, v}), path(u, v, -1);
    else S.insert({u, v}), path(u, v, 1);
    println(T.get());
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

