#include <bits/stdc++.h>
using namespace std;
#ifndef MISAKA
#define OO(x)
#else
#define OO(x) cout << __PRETTY_FUNCTION__ << ": " << #x << " : " << (x) << '\n';
#endif
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
void O(const A& a) {
  cout << a << '\n';
}
template<typename A, typename... B>
void O(const A& a, const B& ...b) {
  cout << a << ' ';
  O(b...);
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
#define FOR(i, j, k) for (int i = (j); i <= (k); ++i)
#define ROF(i, j, k) for (int i = (k); i >= (j); --i)
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
const i64 inf = 1e18, lim = 1e14+1;
int n;
i64 ans;
vector<pii> g[N];
int siz[N];
bool vis[N];

struct Edge {
  int u, v;
  i64 w;
  Edge() : w(lim) {};
  Edge(int _u, int _v, i64 _w) : u(_u), v(_v), w(_w) {};
  bool operator< (const Edge &e) const {
    return w < e.w;
  }
} mne[N];

struct DSU {
  int f[N];
  inline int get(int x) { return f[x] == x ? x : f[x] = get(f[x]); }
  inline int operator[] (const int &x) {
    return f[x];
  }
  inline bool operator() (const Edge& e) {
    if (e.w >= lim) return false;
    if (get(e.u) != get(e.v)) {
      ans += e.w;
      f[f[e.u]] = f[e.v];
      return true;
    }
    return false;
  }
} dsu;
int centroid(int u, int fa) {
  siz[u] = 1;
  int ret = 0;
  bool ok = 1;
  for (auto v : g[u]) if (v.fi != fa && !vis[v.fi]) {
    ret |= centroid(v.fi, u);
    siz[u] += siz[v.fi];
    if (siz[v.fi]*2 > siz[0]) ok = 0;
  }
  if (siz[u]*2 < siz[0]) ok = 0;
  if (ok) return u;
  return ret;
}

struct segT {
  struct f1 {
    i64 v, v1;
    int c, c1;
    int t, t1;
    f1() {
      v = v1 = inf;
      c = c1 = 0;
      t = t1 = 0;
    }
    inline void ins(i64 x, int y, int z) {
      if (x >= v1) return;
      if (y == c) {
        if (x < v) {
          v = x;
          t = z;
        }
      } else{
        if (x < v) {
          v1 = v, c1 = c, t1 = t;
          v = x, c = y, t = z;
        } else if (x < v1) {
          v1 = x;
          t1 = z;
        }
      }
    }
    void operator()(f1 a, const f1& b) {
      *this = a;
      this->ins(b.v, b.c, b.t);
      this->ins(b.v1, b.c1, b.t1);
    }
  };
  struct f2 {
    i64 v, v1;
    int c, c1;
    int t, t1;
    f2() {
      v = v1 = -inf;
      c = c1 = 0;
      t = t1 = 0;
    }
    inline void ins(i64 x, int y, int z) {
      if (x <= v1) return;
      if (y == c) {
        if (x > v) {
          v = x;
          t = z;
        }
      } else {
        if (x > v) {
          v1 = v, c1 = c, t1 = t;
          v = x, c = y, t = z;
        } else if (x > v1) {
          v1 = x;
          t1 = z;
        }
      }
    }
    void operator()(f2 a, const f2& b) {
      *this = a;
      this->ins(b.v, b.c, b.t);
      this->ins(b.v1, b.c1, b.t1);
    }
  };
  struct node {
    int l, r;
    f1 mn;
    f2 mx;
  } a[N<<6];
  int tot, rt;
  inline void init(int &p) {
    if (!p) {
      p = ++tot;
      a[tot] = a[0];
    }
  }
  inline void clr() {
    tot = 0;
    rt = 0;
  }
  i64 v;
  int c, u;
  inline void ins(int &p, i64 l, i64 r) {
    init(p);
    if (r - l == 1) {
      a[p].mn.ins(v, c, u);
      a[p].mx.ins(v, c, u);
      return;
    }
    i64 m = (l + r) >> 1;
    if (v < m) ins(a[p].l, l, m);
    else ins(a[p].r, m, r);
    a[p].mn(a[a[p].l].mn, a[a[p].r].mn);
    a[p].mx(a[a[p].l].mx, a[a[p].r].mx);
  }
  f2 getf2(int p, i64 l, i64 r, i64 s, i64 t) {
    if (l == s && r == t) {
      return a[p].mx;
    }
    f2 ret;
    i64 m = (l + r) >> 1;
    if (s < m) ret(ret, getf2(a[p].l, l, m, s, min(m, t)));
    if (t > m) ret(ret, getf2(a[p].r, m, r, max(s, m), t));
    return ret;
  }
  f1 getf1(int p, i64 l, i64 r, i64 s, i64 t) {
    if (l == s && r == t) {
      return a[p].mn;
    }
    f1 ret;
    i64 m = (l + r) >> 1;
    if (s < m) ret(ret, getf1(a[p].l, l, m, s, min(m, t)));
    if (t > m) ret(ret, getf1(a[p].r, m, r, max(s, m), t));
    return ret;
  }
  inline void ins(i64 _v, int _c, int _u) {
    v = _v;
    u = _u;
    c = _c;
    ins(rt, -lim, lim);
  }
  inline Edge operator()(i64 w, int c, int u) {
    auto l = getf2(rt,-lim,lim,-lim,-w+1);
    Edge ret;
    if (l.c == c) chkmin(ret, Edge(u, l.t1, abs(w+l.v1)));
    else chkmin(ret, Edge(u, l.t, abs(w+l.v)));
    auto r = getf1(rt,-lim,lim,-w,lim);
    if (r.c == c) chkmin(ret, Edge(u, r.t1, abs(w+r.v1)));
    else chkmin(ret, Edge(u, r.t, abs(w+r.v)));
    return ret;
  }
} T;

void dfs(int u, int fa, i64 dis) {
  chkmin(mne[dsu[u]], T(dis, dsu[u], u));
  for (auto v : g[u]) if (v.fi != fa && !vis[v.fi]) {
    dfs(v.fi, u, dis + v.se);
  }
}
void dfs2(int u, int fa, i64 dis) {
  T.ins(dis, dsu[u], u);
  for (auto v : g[u]) if (v.fi != fa && !vis[v.fi]) {
    dfs2(v.fi, u, dis + v.se);
  }
}

vector<int> g1[N];
void build(int u) {
  vis[u] = 1;
  centroid(u, 0);
  for (auto v : g[u]) if (!vis[v.fi]) {
    siz[0] = siz[v.fi];
    int to = centroid(v.fi, u);
    g1[u].pb(to);
    build(to);
  }
}

void work(int u) {
  vis[u] = 1;
  T.clr();
  T.ins(0, dsu[u], u);
  for (auto v : g[u]) if (!vis[v.fi]) {
    dfs(v.fi, u, v.se);
    dfs2(v.fi, u, v.se);
  }
  T.clr();
  ROF(i,0,g[u].size()-1) if (!vis[g[u][i].fi]) {
    auto &v = g[u][i];
    dfs(v.fi, u, v.se);
    dfs2(v.fi, u, v.se);
  }
  chkmin(mne[dsu[u]], T(0, dsu[u], u));
  for (auto v : g1[u]) {
    work(v);
  }
}

inline void solve() {
  rd(n);
  FOR(i,2,n) {
    int u, w, v;
    rd(u,v,w);
    g[u].eb(v,w);
    g[v].eb(u,w);
  }
  iota(dsu.f+1, dsu.f+n+1, 1);
  int cnt = 0;
  siz[0] = n;
  int rt = centroid(1,0);
  build(rt);
  while (cnt < n - 1) {
    FOR(i,1,n) vis[i] = 0;
    FOR(i,1,n) mne[i] = mne[0];
    work(rt);
    FOR(i,1,n) cnt += dsu(mne[i]);
    FOR(i,1,n) dsu.get(i);
  }
  O(ans);
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

