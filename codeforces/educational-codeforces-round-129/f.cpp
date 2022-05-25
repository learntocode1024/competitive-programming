/** @file
 * @ingroup dynamic_connectivity virt_tree


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
const int N = 5e5+5;

struct hist {
  int *x;
  int c;
  inline void operator() () {
    *x = c;
  }
} H[N<<2];
int tl;

inline void let(int &x, int c) {
  ++tl;
  H[tl].x = &x;
  H[tl].c = x;
  x = c;
}

int f[N], siz[N];
int get(int x) {
  return x == f[x] ? x : get(f[x]);
}
inline void link(int u, int v) {
  u = get(u);
  v = get(v);
  if (u != v) {
    if (siz[u] < siz[v]) swap(u, v);
    let(f[v], u);
    let(siz[u], siz[u] + siz[v]);
  }
}

vector<int> g[N<<2];
vector<pii> e[N];
i64 ans = 0;

void add(int p, int l, int r, int s, int t, int v) {
  if (l == s && r == t) {
    g[p].pb(v);
    return;
  }
  int m = (l + r) >> 1;
  if (s <= m) add(p<<1, l, m, s, min(m, t), v);
  if (t > m) add(p<<1|1, m+1, r, max(m+1, s), t, v);
}

void solve(int p, int l, int r) {
  int hd = tl;
  for (auto u : g[p])
    for (auto &[x, y] : e[u])
      link(x, y);
  if (l == r) {
    for (auto &[u, v] : e[l]) {
      ans += 1ll * siz[get(u)] * siz[get(v)];
    }
  } else {
    int m = (l + r) >> 1;
    solve(p<<1, l, m);
    solve(p<<1|1, m+1, r);
  }
  while (tl > hd) H[tl--]();
}

inline void sol() {
  int n;
  rd(n);
  FOR(i,1,n) f[i] = i, siz[i] = 1;
  FOR(i,1,n-1) {
    int u, v, w;
    rd(u, v, w);
    e[w].eb(u, v);
  }
  FOR(i,1,n) {
    if (i > 1) add(1,1,n,1,i-1,i);
    if (i < n) add(1,1,n,i+1,n,i);
  }
  solve(1, 1, n);
  O(ans);
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

