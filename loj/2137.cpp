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
vector<int> g0[N], g[N<<1];
int low[N], dfn[N], s[N], t, e;
int n, m;
int f[N<<1], sz[N<<1];
int all[N], sa, id;
bool vis[N<<1];
i64 ans = 0;

void calc(int u, int fa) {
  vis[u] = 1;
  if (u <= n) ++sz[u];
  i64 a = 0;
  for (auto v : g[u]) if (v != fa) {
    calc(v, u);
    sz[u] += sz[v];
    a += 1ll * sz[v] * (sz[v]-1);
  }
  if (u <= n) {
    ans += (1ll * (sa-1) * sa - a - (sa-sz[u]) * (sa-sz[u]-1)) * f[u];
  } else {
    ans += (1ll * (sa-1)*sa - a - (sa-sz[u]) * (sa-sz[u]-1)) * f[u];
  }
}

void dfs(int u, int fa) {
  static int tot = 0;
  ++all[id];
  low[u] = dfn[u] = ++tot;
  f[u] = -1;
  for (auto v : g0[u]) if (v != fa) {
    if (!dfn[v]) {
      s[++t] = v;
      dfs(v, u);
      chkmin(low[u], low[v]);
      if (low[v] >= dfn[u] && (fa || g0[u].size()>1)) {
        ++e;
        f[e] = 1;
        g[e].pb(u);
        g[u].pb(e);
        int tp;
        do {
          tp = s[t--];
          g[e].pb(tp);
          g[tp].pb(e);
          ++f[e];
        } while (t && tp != v);
      }
    } else chkmin(low[u], dfn[v]);
  }
}

inline void solve() {
  rd(n, m);
  FOR(i, 0, m) {
    int u, v;
    rd(u, v);
    g0[u].pb(v);
    g0[v].pb(u);
  }
  e = n;
  for (int i = 1; i <= n; ++i) if (!dfn[i]) {
    id = i;
  s[++t] = i;
  dfs(i, 0);
  ++e;
  while (t) {
    g[e].pb(s[t]);
    g[s[t--]].pb(e);
    ++f[e];
  }
  }
  FOR(i, 1, n + 1) if (!vis[i]) {
    sa = all[i];
    calc(i, 0);
  }
  println(ans);
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

