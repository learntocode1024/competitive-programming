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
int f[N];
int get(int x) { return (x == f[x]) ? x : f[x] = get(f[x]); }
int n;
vector<pii> g[N];
i64 ans;

bool merge(int u, int v) {
  if (get(u) == get(v)) return false;
  f[f[u]] = f[v];
  return true;
}

namespace Else {
i64 dis[N], d[N];
bool vis[N];

void dfs(int u, int fa) {
  if (!vis[u]) chkmin(dis[u], abs(d[u]));
  for (auto v : g[u]) if (v.fi != fa) {
    d[v.fi] = d[u] + v.se;
    dfs(v.fi,u);
  }
}

void work() {
  dis[1] = 0;
  dis[0] = 1e17;
  FOR(i,2,n) dis[i] = 1e17;
  FOR(_,1,n) {
    int u = 0;
    FOR(i,1,n) if (!vis[i]&&dis[i]<dis[u]) u = i;
    ans += dis[u];
    vis[u] = 1;
    d[u] = 0;
    dfs(u,0);
  }
}
}

namespace sub3 {
vector<int> bel[N];
int f1[N];
set<pii> S;
void work() {
  for (auto v : g[1]) {
    S.insert({v.se,v.fi});
  }
  iota(f+1,f+n+1,1);
  while (true) {
    int grp = 0;
    FOR(i,1,n) bel[i].clear();
    FOR(i,1,n) bel[f1[i] = get(i)].pb(i);
    FOR(i,1,n) grp += bel[i].size() >= 1;
    if (grp == 1) break;
    FOR(i,1,n) if (!bel[i].empty()) {
      i64 w = 3e9;
      int u = -1, s = -1;
      if (f1[1] != i) {
        for (auto v : bel[i]) {
          int cw = abs(g[v][0].se);
          if (cw < w) u = 1, w = cw, s = v;
        }
      }
      for (auto v : bel[i]) {
        if (v!=1) S.erase({g[v][0].se, v});
      }
      if (!S.empty()) for (auto v : bel[i]) {
        int cw = -g[v][0].se;
        if (v == 1) cw = 0;
        auto it = S.lower_bound({cw, 0});
        if (it != S.end()) {
          if (abs(it->fi - cw) < w) w = abs(it->fi-cw), s = v, u = it->se;
        }
        if (it != S.begin()) {
          --it;
          if (abs(it->fi - cw) < w) w = abs(it->fi-cw), s = v, u = it->se;
        }
      }
      for (auto v : bel[i]) {
        if (v!=1) S.insert({g[v][0].se, v});
      }
      if (merge(s,u)) ans += w;
    }
  }
}
}

inline void solve() {
  rd(n);
  bool sub3 = 1;
  FOR(i,2,n) {
    int u, v, w;
    rd(u,v,w);
    if (u != 1) sub3 = 0;
    g[u].eb(v,w);
    g[v].eb(u,w);
  }
  if (sub3) sub3::work();
  else Else::work();
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

