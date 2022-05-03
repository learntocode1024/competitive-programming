#include <bits/stdc++.h>
using namespace std;
template <typename T> inline void O(const T &x) { cout << x << '\n'; }
template <typename T, typename... W> inline void O(const T &x, const W &...b) {
  cout << x << ' ';
  O(b...);
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
const int N = 3e5+5;
vector<int> g[N], g1[N];
int n, m, t;
int scc[N];
int lo[N], hi[N];
int ro[N];
namespace get_scc {
int ord[N], tot;
bool vis[N];

void dfs1(int u) {
  vis[u] = 1;
  for (auto v : g[u]) if (!vis[v]) dfs1(v);
  ord[++tot] = u;
}
int oo;
void dfs2(int u) {
  scc[u] = t;
  ro[++oo] = u;
  for (auto v : g1[u]) if (!scc[v]) dfs2(v);
}

inline void work() {
  FOR(i,1,n) if (!vis[i]) dfs1(i);
  ROF(i,1,n) {
    if (scc[ord[i]]) continue;
    ++t;
    dfs2(ord[i]);
  }
}
}

struct sgT {
  int tr[N<<2];
  void set(int p, int l, int r, int s, int t, int c) {
    if (l == s && r == t) {
      tr[p] = c;
      return;
    }
    int m = (l + r) >> 1;
    if (tr[p]) {
      tr[p<<1] = tr[p<<1|1] = tr[p];
      tr[p] = 0;
    }
    if (s <= m) set(p<<1, l, m, s, min(m, t), c);
    if (t > m) set(p<<1|1, m+1, r, max(s, m+1), t, c);
  }
  int get(int p, int l, int r, int v) {
    if (l == r) return tr[p];
    int m = (l + r) >> 1;
    if (tr[p]) {
      tr[p<<1] = tr[p<<1|1] = tr[p];
      tr[p] = 0;
    }
    if (v <= m) return get(p<<1, l, m, v);
    else return get(p<<1|1, m+1, r, v);
  }

} T;

int L[N], R[N];
vector<int> q[N];

int c[N];
void ins(int x, int v) {
  for (; x <= n; x += x & -x) c[x] += v;
}

int get(int x) {
  int y = 0;
  for(; x; x -= x & -x) y += c[x];
  return y;
}

inline void sol() {
  cin >> n >> m;
  FOR(i,1,m) {
    int x, y;
    cin >> x >> y;
    g[x].pb(y);
    g1[y].pb(x);
  }
  get_scc::work();
  FOR(i,1,t) lo[i] = n+1;
  FOR(i,1,n) ckmin(lo[scc[i]], i);
  FOR(i,1,n) ckmax(hi[scc[i]], i);
  ROF(i,1,n) {
    for (auto v : g[ro[i]]) ckmin(lo[scc[ro[i]]], lo[scc[v]]), ckmax(hi[scc[ro[i]]], hi[scc[v]]);
  }
  FOR(i,1,n) {
    if(hi[scc[i]] == i) {
      L[i] = i == n ? 1 : T.get(1,1,n,i+1)+1;
    } else T.set(1,1,n,i,hi[scc[i]],i);
  }
  T.set(1,1,n,1,n,n+1);
  ROF(i,1,n) {
    if (lo[scc[i]] == i) {
      R[i] = i == 1 ? n : T.get(1,1,n,i-1) - 1;
    } else T.set(1,1,n,lo[scc[i]], i, i);
  }
  FOR(i,1,n) {
    if (R[i] && R[i] >= hi[scc[i]]) {
      q[hi[scc[i]]].pb(i);
      q[R[i]+1].pb(-i);
    }
  }
  i64 ans = 0;
  FOR(i,1,n) {
    for (auto v : q[i]) {
      if (v > 0) ins(v, 1);
      else ins(-v, -1);
    }
    if (L[i] && L[i] <= lo[scc[i]]) ans += get(lo[scc[i]]) - get(L[i]-1);
  }
  O(ans%int(1e9+7));
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

