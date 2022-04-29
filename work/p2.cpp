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
const int N = 1e6+5;
const int P = 998244353;
int id[N];
vector<int> g[N];
int f[N], l[N], r[N], l2[N], r2[N];
int n, q;
i64 mx = 0;
i64 del = 0;

struct seg {
  struct node {
    int mx;
    int s1, s2;
    int tg;
    inline void operator() (i64 c, int l, int r) {
      tg = (tg + c) % P;
      s2 = (s2 + c * c % P * (r - l) + 2 * c * s1) % P;
      s1 = (s1 + (r - l) * c) % P;
    }
  } a[N<<2];
  inline void down(int p, int l, int r) {
    if (a[p].tg) {
      int m = (l + r) >> 1;
      a[p<<1](a[p].tg, l, m);
      a[p<<1|1](a[p].tg, m, r);
      a[p].tg = 0;
    }
  }
  inline void up(int p) {
    a[p].s1 = (a[p<<1].s1 + a[p<<1|1].s1) % P;
    a[p].s2 = (a[p<<1].s2 + a[p<<1|1].s2) % P;
  }
  int mx(int p, int l, int r, int s, int t) {
    if (l == s && r == t) return a[p].mx;
    int m = (l + r) >> 1;
    int ret = 0;
    if (s < m) ret = mx(p<<1,l,m,s,min(m,t));
    if (t > m) chkmax(ret, mx(p<<1|1,m,r,max(m,s),t));
    return ret;
  }
  void ch(int p, int l, int r, int s, int v) {
    if (r - l == 1) {
      a[p].mx += v;
      return;
    }
    int m = (l + r) >> 1;
    if (s < m) ch(p<<1,l,m,s,v);
    else ch(p<<1|1,m,r,s,v);
    a[p].mx = max(a[p<<1].mx, a[p<<1|1].mx);
  }
  void add(int p, int l, int r, int s, int t, int v) {
    if (l == s && r == t) return a[p](v,l,r);
    int m = (l + r) >> 1;
    down(p,l,r);
    if (s < m) add(p<<1,l,m,s,min(m,t),v);
    if (t > m) add(p<<1|1,m,r,max(m,s),t,v);
    up(p);
  }
} T;

inline void bfs() {
  int tot = 0;
  static int qu[N];
  int hd = 1, tl = 1;
  qu[1] = 1;
  while (hd <= tl) {
    int u = qu[hd++];
    id[u] = ++tot;
    for (auto v : g[u]) if (!id[v]) qu[++tl] = v;
  }
  FOR(u,1,n) {
    l[u] = n+1;
    for (auto v : g[u]) {
      if (id[v] < id[u]) f[u] = v;
      else chkmin(l[u], id[v]), chkmax(r[u], id[v]);
    }
  }
  FOR(u,1,n) {
    l2[u] = n+1;
    for (auto v : g[u]) {
      if (id[v] > id[u]) chkmin(l2[u], l[v]), chkmax(r2[u], r[v]);
    }
  }
}

int w[N];
inline void add(int u, int x) {
  del = (del + P - 1ll * w[u] * w[u] % P * g[u].size() % P) % P;
  w[u] += x;
  if (l[u] != n+1) T.add(1,1,n+1,l[u],r[u]+1,x);
  if (f[u]) T.add(1,1,n+1,id[f[u]],id[f[u]]+1,x);
  if (l2[u] != n+1) {
    chkmax(mx, 1ll * w[u] * T.mx(1,1,n+1,l2[u], r2[u]+1));
  }
  if (f[u]) {
    int L = l[f[u]], R = r[f[u]];
    if (L != id[u]) 
      chkmax(mx, 1ll * w[u] * T.mx(1,1,n+1,L, id[u]));
    if (R != id[u])
      chkmax(mx, 1ll * w[u] * T.mx(1,1,n+1,id[u]+1,R+1));
    if (f[f[u]]) chkmax(mx, 1ll * w[u] * w[f[f[u]]]);
  }
  T.ch(1,1,n+1,id[u],x);
  del = (del + 1ll * w[u] * w[u] % P * g[u].size()) % P;
  //O("debug",T.a[1].s2);
}

inline void solve() {
  rd(n, q);
  FOR(i,2,n) {
    int x, y;
    rd(x, y);
    g[x].pb(y);
    g[y].pb(x);
  }
  bfs();
  FOR(i,1,n) {
    int x;
    rd(x);
    add(i, x);
  }
  while (q--) {
    int op;
    rd(op);
    if (op == 1) {
      O(mx, (T.a[1].s2 + P - del) % P);
    } else {
      int u, x;
      rd(u,x);
      add(u,x);
    }
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

