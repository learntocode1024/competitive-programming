#include <bits/stdc++.h>
#include "atcoder/lazysegtree"
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
i64 e() { return 0ll; }
i64 id() { return 0ll; }
inline i64 F(i64 a, i64 b) { return min(a,b); }
inline i64 G(i64 a, i64 b) { return a+b; }
using sgT = atcoder::lazy_segtree<i64, F, e, i64, G, G, id>;
sgT T[2];
bool col[N];
vector<i64> P;
vector<int> g[N];
i64 p[N], c[N];
int siz[N], son[N], dfn[N], hd[N], f[N];

void dfs(int u, int fa) {
  col[u] = col[fa] ^ 1;
  siz[u] = 1;
  f[u] = fa;
  for (auto v : g[u]) if (v != fa) {
    dfs(v,u);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
    p[u] -= p[v];
  }
}

void d2(int u, int h, int fa) {
  static int tot = 0;
  hd[u] = h;
  dfn[u] = tot++;
  if (son[u]) d2(son[u], h, u);
  for (auto v : g[u]) if (v != son[u] && v != fa) {
    d2(v,v,u);
  }
}

inline void solve() {
  int n, q;
  rd(n, q);
  FOR(i,1,n) rd(p[i]), c[i] = p[i];
  FOR(i,2,n) {
    int u, v;
    rd(u,v);
    g[u].pb(v);
    g[v].pb(u);
  }
  P = vector<i64>(n);
  dfs(1,0);
  d2(1,1,1);
  FOR(i,1,n) if (col[i]) {
    P[dfn[i]] = 1e15;
  } else P[dfn[i]] = p[i];
  T[0] = sgT(P);
  FOR(i,1,n) if (!col[i]) {
    P[dfn[i]] = 1e15;
  } else P[dfn[i]] = p[i];
  T[1] = sgT(P);
  while (q--) {
    int x, y;
    rd(x, y);
    int d = y - c[x];
    c[x] = y;
    int c = col[x];
    while (x) {
      T[c].apply(dfn[hd[x]], dfn[x]+1,d);
      T[c^1].apply(dfn[hd[x]], dfn[x]+1,-d);
      x = f[hd[x]];
    }
    if (T[1].get(0) != 0 || T[1].all_prod() < 0 || T[0].all_prod() < 0) O("No");
    else O("Yes");
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

