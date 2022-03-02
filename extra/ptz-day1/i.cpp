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
const int N = 1e5+5;
vector<int> g[N];
int n;
int sz[N], rk[N], id[N], son[N], f[N], hd[N], tot;
int A[N], C[N];
i64 AA[N];
void dfs1(int u) {
  sz[u] = 1;
  for (auto v : g[u]) {
    dfs1(v);
    sz[u] += sz[v];
    AA[u] += AA[v];
    if (sz[v] > sz[son[u]]) son[u] = v;
  }
}

void dfs2(int u, int up) {
  hd[u] = up;
  id[u] = ++tot;
  rk[tot] = u;
  if (son[u]) dfs2(son[u], up);
  for (auto v : g[u]) if (v != son[u]) {
    dfs2(v, v);
  }
}

struct seg {
  struct node {
    i64 a, tg;
  } a[N<<2];
  void build(int p, int l, int r) {
    if (r - l == 1) {
      a[p].a = AA[rk[l]];
      return;
    }
    int mid = (l + r) >> 1;
    build(p<<1,l,mid);
    build(p<<1|1, mid, r);
    a[p].a = min(a[p<<1].a, a[p<<1|1].a);
  }
  void ch(int p, int l, int r, int s, int t, int v) {
    if (l == s && r == t) {
      a[p].a += v;
      a[p].tg += v;
      return;
    }
    if (a[p].tg) {
      i64 tg = a[p].tg;
      a[p<<1].a += tg;
      a[p<<1].tg += tg;
      a[p<<1|1].a += tg;
      a[p<<1|1].tg += tg;
      a[p].tg = 0;
    }
    int mid = (l + r) >> 1;
    if (s < mid) ch(p<<1,l,mid,s,min(mid,t),v);
    if (t > mid) ch(p<<1|1,mid,r,max(mid,s),t,v);
    a[p].a = min(a[p<<1].a, a[p<<1|1].a);
  }
} T;

inline void ret() {
  println(T.a[1].a < 0 ? "No" : "Yes");
}

inline void solve() {
  rd(n);
  FOR(i, 2, n + 1) {
    rd(f[i]);
    g[f[i]].pb(i);
  }
  FOR(i, 1, n + 1) rd(A[i]);
  FOR(i, 1, n + 1) {rd(C[i]), AA[i] = A[i] - C[i];}
  dfs1(1);
  dfs2(1, 1);
  T.build(1,1,n+1);
  ret();
  int q;
  rd(q);
  while (q--) {
    int t, v, x;
    rd(t, v, x);
    int d;
    if (t==1) {
      d = x - A[v];
      A[v] = x;
    } else {
      d = C[v] - x;
      C[v] = x;
    }
    while (v) {
      T.ch(1,1,n+1,id[hd[v]],id[v]+1,d);
      v = f[hd[v]];
    }
    ret();
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

