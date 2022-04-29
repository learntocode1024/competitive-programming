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
const int N = 2e6+5;
vector<int> g[N], G[N<<1];
int n, n1;
int low[N], dfn[N];
int tt, s[N];

void tarjan(int u) {
  static int tot = 0;
  dfn[u] = low[u] = ++tot;
  s[++tt] = u;
  for (auto v : g[u]) {
    if (!dfn[v]) {
      tarjan(v);
      chkmin(low[u], low[v]);
      if (dfn[u] == low[v]) {
        ++n1;
        int x;
        do {
          x = s[tt--];
          G[n1].pb(x);
          G[x].pb(n1);
        } while (x != v);
        G[u].pb(n1);
        G[n1].pb(u);
      }
    } else chkmin(low[u], dfn[v]);
  }
}

int d[N<<1], son[N<<1];

void dfs(int u, int fa) {
  for (auto v : G[u]) if (v != fa) {
    dfs(v, u);
    if (d[v] + 1 > d[son[u]]) son[u] = v;
  }
  d[u] = d[son[u]] + 1;
}

i64 ans = 0;
list<int> f[N<<1];
decltype(f[0].size()) L;

void dfs2(int u, int fa) {
  if (son[u]) {
    dfs2(son[u], u);
    f[u].swap(f[son[u]]);
  }
  if (u <= n) {
    f[u].push_front(1);
    if (f[u].size() > L) f[u].pop_back();
    if (f[u].size() == L) ans += *f[u].rbegin();
  }
  for (auto v : G[u]) if (v != fa && v != son[u]) {
    dfs2(v, u);
    auto l = f[v].begin();
    auto r = f[u].rbegin();
    if (f[u].size() == L) ++r;
    for (int i = 1; i <= min(f[v].size(), L - 1); ++i) {
      if (min(L-1, f[u].size()) + i < L) {
        ++l;
        continue;
      }
      ans += 1ll * *l * *r;
      ++l;
      ++r;
    }
    auto to = f[u].begin();
    if (u <= n) ++to;
    l = f[v].begin();
    for (int i = 1; i <= min(f[v].size(), L - 1); ++i) {
      *to += *l;
      ++to;
      ++l;
    }
  }
}

inline void solve() {
  int m;
  rd(n, m, L);
  FOR(i,1,m) {
    int u, v;
    rd(u,v);
    g[u].pb(v);
    g[v].pb(u);
  }
  n1 = n;
  tarjan(1);
  // ++n1;
  // while (tt) {
  //   G[s[tt]].pb(n1);
  //   G[n1].pb(s[tt--]);
  // }
  // FOR(i,1,n1) for (auto v : G[i]) O(i,v);
  dfs(1, 0);
  dfs2(1, 0);
  O(ans<<1);
}

int main() {
#ifndef MISAKA
  freopen("sing.in", "r", stdin);
  freopen("sing.out", "w", stdout);
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

