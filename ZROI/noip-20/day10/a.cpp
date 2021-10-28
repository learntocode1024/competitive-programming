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

const int N = 1e4+5, M = 5e5+5;
const int inf = 1e8;
vector<pii> g[N];
int d1[N], d2[N];
priority_queue<pii> pq;
bool vis[N], is[N];
int tot;
int dfn[N], low[N], lst[N];
int n, m;

void dfs(int u, int fa) {
  vis[u] = 1;
  low[u] = dfn[u] = ++tot;
  int ch = 0;
  for (auto v : g[u]) {
    if (!vis[v.fi]) {
      ch++;
      dfs(v.fi, u);
      low[u] = min(low[u], low[v.fi]);
      if (fa != u && low[v.fi] >= dfn[u] && !is[u])
        is[u] = 1;
    } else if (v.fi != fa)
      low[u] = min(low[u], dfn[v.fi]);
  }
  if (fa == u && ch >= 2 && !is[u]) {
    is[u] = 1;
  }
}

inline void getcut() {
  FOR(i, 1, n + 1) if (!vis[i])
    tot = 0, dfs(i, i);
}

inline void dijk(int *d, int ori) {
  FOR(i, 1, n + 1) d[i] = inf;
  d[ori] = 0;
  pq.emplace(0, ori);
  while (!pq.empty()) {
    auto u = pq.top();
    pq.pop();
    if (vis[u.se]) continue;
    vis[u.se] = 1;
    for (auto v : g[u.se]) {
      if (!vis[v.fi] && d[v.fi] > d[u.se] + v.se) {
        d[v.fi] = d[u.se] + v.se;
        lst[v.fi] = u.se;
        pq.emplace(-d[v.fi], v.fi);
      }
    }
  }
}

int all[N], tt;

inline void solve() {
  cin >> n >> m;
  FOR(i, 0, m) {
    int x, y, d;
    cin >> x >> y >> d;
    if (x == y) continue;
    g[x].eb(y, d);
    g[y].eb(x, d);
  }
  int C, I, T;
  cin >> C >> I >> T;
  if (C == I) {
    puts("-1");
    return;
  }
  getcut();
  FOR(i, 1, n + 1) vis[i] = 0;
  vis[I] = 1;
  dijk(d1, C);
  if (d1[T] == inf) {
    puts("-1");
    return;
  }
  all[0] = C;
  all[1] = T;
  tt = 2;
  for (int i = T; i != C; i = lst[i]) {
    if (is[i]) {
      all[tt++] = i;
    }
  }
  FOR(i, 1, n + 1) vis[i] = 0;
  dijk(d2, I);
  long double ans = 0;
  for (int i = 0; i < tt; ++i) {
    if (!d2[all[i]]) {
      puts("-1");
      return;
    }
    ans = fmax(ans, (long double) d1[all[i]] / d2[all[i]]);
  }
  cout << fixed << setprecision(20) << ans << '\n';
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

