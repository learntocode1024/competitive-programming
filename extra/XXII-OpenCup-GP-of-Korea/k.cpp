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
const int inf = 1919810;
int p1[N], p2[N], p3[N];
int r1[N], r2[N], r3[N];
int n;

struct SEGT_MN {
  int c[N<<2];
  #define lc (p<<1)
  #define rc (p<<1|1)
  int _A[N], _R[N];
  void _build(int p, int l, int r) {
    if (r - l == 1) {
      c[p] = _A[l];
      return;
    }
    int mid = (l + r) >> 1;
    _build(lc, l, mid);
    _build(rc, mid, r);
    c[p] = min(c[lc], c[rc]);
  }
  int get(int p, int l, int r, int s, int t) {
    if (l == s && r == t) return c[p];
    int mid = (l + r) >> 1;
    if (t <= mid) return get(lc, l, mid, s, t);
    if (s >= mid) return get(rc, mid, r, s, t);
    return min(get(lc, l, mid, s, mid), get(rc, mid, r, mid, t));
  }
  void ch(int p, int l, int r, int s) {
    if (r == l + 1) {
      c[p] = inf;
      return;
    }
    int mid = (l + r) >> 1;
    if (s < mid) ch(lc, l, mid, s);
    else ch(rc, mid, r, s);
    c[p] = min(c[lc], c[rc]);
  }
  inline void build(int *a) {
    copy(a + 1, a + n + 1, _A + 1);
    FOR(i, 1, n + 1) _R[_A[i]] = i;
    _build(1, 1, n + 1);
  }
  inline void del(int x) {
    ch(1, 1, n + 1, x);
  }
  inline int get(int x) {
    int ret = get(1, 1, n + 1, 1, x + 1);
    if (min(ret, _A[x]) == _A[x]) return -1;
    return _R[ret];
  }
};

struct SEGT_MX {
  int c[N<<2];
  #define lc (p<<1)
  #define rc (p<<1|1)
  int _A[N], _R[N];
  void _build(int p, int l, int r) {
    if (r - l == 1) {
      c[p] = _A[l];
      return;
    }
    int mid = (l + r) >> 1;
    _build(lc, l, mid);
    _build(rc, mid, r);
    c[p] = max(c[lc], c[rc]);
  }
  int get(int p, int l, int r, int s, int t) {
    if (l == s && r == t) return c[p];
    int mid = (l + r) >> 1;
    if (t <= mid) return get(lc, l, mid, s, t);
    if (s >= mid) return get(rc, mid, r, s, t);
    return max(get(lc, l, mid, s, mid), get(rc, mid, r, mid, t));
  }
  void ch(int p, int l, int r, int s) {
    if (r == l + 1) {
      c[p] = 0;
      return;
    }
    int mid = (l + r) >> 1;
    if (s < mid) ch(lc, l, mid, s);
    else ch(rc, mid, r, s);
    c[p] = max(c[lc], c[rc]);
  }
  inline void build(int *a) {
    copy(a + 1, a + n + 1, _A + 1);
    FOR(i, 1, n + 1) _R[_A[i]] = i;
    _build(1, 1, n + 1);
  }
  inline void del(int x) {
    ch(1, 1, n + 1, x);
  }
  inline int get(int x) {
    int ret = get(1, 1, n + 1, x, n + 1);
    if (max(ret, _A[x]) == _A[x]) return -1;
    return _R[ret];
  }
};

int tmp[N];

struct DS1 {
  SEGT_MN t12, t13, t23;
  inline void init() {
    FOR(i, 1, n + 1) tmp[i] = p2[r1[i]];
    t12.build(tmp);
    FOR(i, 1, n + 1) tmp[i] = p3[r1[i]];
    t13.build(tmp);
    FOR(i, 1, n + 1) tmp[i] = p3[r2[i]];
    t23.build(tmp);
  }
  inline void del(int u) {
    t12.del(p1[u]);
    t13.del(p1[u]);
    t23.del(p2[u]);
  }
  inline int nxt(int u) {
    int ret = t12.get(p1[u]);
    if (ret == -1) ret = t13.get(p1[u]);
    if (ret != -1) {
      t12.del(ret);
      t13.del(ret);
      t23.del(p2[r1[ret]]);
      return r1[ret];
    } else {
      ret = t23.get(p2[u]);
      if (ret == -1) return -1;
      t12.del(p1[r2[ret]]);
      t13.del(p1[r2[ret]]);
      t23.del(ret);
      return r2[ret];
    }
    return -1;
  }
} T2;

struct DS2 {
  SEGT_MX t12, t13, t23;
  inline void init() {
    FOR(i, 1, n + 1) tmp[i] = p2[r1[i]];
    t12.build(tmp);
    FOR(i, 1, n + 1) tmp[i] = p3[r1[i]];
    t13.build(tmp);
    FOR(i, 1, n + 1) tmp[i] = p3[r2[i]];
    t23.build(tmp);
  }
  inline void del(int u) {
    t12.del(p1[u]);
    t13.del(p1[u]);
    t23.del(p2[u]);
  }
  inline int nxt(int u) {
    int ret = t12.get(p1[u]);
    if (ret == -1) ret = t13.get(p1[u]);
    if (ret != -1) {
      t12.del(ret);
      t13.del(ret);
      t23.del(p2[r1[ret]]);
      return r1[ret];
    } else {
      ret = t23.get(p2[u]);
      if (ret == -1) return -1;
      t12.del(p1[r2[ret]]);
      t13.del(p1[r2[ret]]);
      t23.del(ret);
      return r2[ret];
    }
    return -1;
  }
} T1;

int rnk[N], f[N], tot;
bool vis[N];
int scc[N], cnt;

void dfs1(int u) {
  int v = T1.nxt(u);
  while (v != -1) {
    dfs1(v);
    v = T1.nxt(u);
  }
  vis[u] = 1;
  rnk[++tot] = u;
}

void dfs2(int u) {
  scc[u] = cnt;
  if (!f[cnt]) f[cnt] = u;
  int v = T2.nxt(u);
  while (v != -1) {
    dfs2(v);
    v = T2.nxt(u);
  }
}

int pos[N];
bool cmp(int b, int a) {
  if (a == b) return 0;
  return p1[a] > p1[b] ? (p2[a] > p2[b] || p3[a] > p3[b]) : (p2[a] > p2[b] && p3[a] > p3[b]);
}

inline void build_scc() {
  FOR(i, 1, n + 1)
    if (!vis[i])
      T1.del(i), dfs1(i);
  ROF(i, 1, n + 1)
    if (!scc[rnk[i]])
      ++cnt, T2.del(rnk[i]), dfs2(rnk[i]);
}

bool scc_path(int u, int v) {
  if (scc[u] == scc[v]) return true;
  return cmp(u, v);
}

inline void solve() {
  cin >> n;
  FOR(i, 1, n + 1) rd(p1[i], p2[i], p3[i]);
  FOR(i, 1, n + 1) r1[p1[i]] = r2[p2[i]] = r3[p3[i]] = i;
  T1.init();
  T2.init();
  build_scc();
  int q;
  cin >> q;
  while (q--) {
    int u, v;
    cin >> u >> v;
    println(scc_path(u, v) ? "YES" : "NO");
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
