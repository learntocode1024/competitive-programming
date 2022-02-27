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
int n;
vector<int> g[N];
int tot;
bool vis[N];
int c[N];
map<int, int> d[N];
priority_queue<pii, vector<pii>, greater<pii> > pq;
int s[N], t[N], tt;
int sz = 0;

void dfs(int u, int fa) {
  ++sz;
  vis[u] = 1;
  if (c[u]) d[tot][u] = c[u];
  for (auto v : g[u]) if (v != fa && !vis[v]) {
    dfs(v, u);
  }
}

inline void solve() {
  int m;
  rd(n, m);
  FOR(i, 1, n + 1) cin >> c[i];
  FOR(i, 0, m) {
    int u, v;
    rd(u, v);
    g[u].pb(v);
    g[v].pb(u);
    --c[u], --c[v];
  }
  FOR(i, 1, n + 1) if (!vis[i]) {++tot; sz = 0; dfs(i, 0); pq.push(mkp(sz, tot));}
  while (pq.size()>1) {
    int v = pq.top().se;
    int sz = pq.top().fi;
    pq.pop();
    int u = pq.top().se;
    sz += pq.top().fi;
    pq.pop();
    if (d[u].empty()||d[v].empty()) {
      println(-1);
      return;
    }
    s[tt] = d[u].begin()->fi;
    t[tt] = d[v].begin()->fi;
    ++tt;
    --d[u].begin()->se;
    --d[v].begin()->se;
    if (d[u].begin()->se == 0) d[u].erase(d[u].begin());
    if (d[v].begin()->se == 0) d[v].erase(d[v].begin());
    for (auto x : d[v]) {
      d[u].insert(x);
    }
    d[v].clear();
    pq.push(mkp(sz, u));
  }
  if (!d[pq.top().se].empty()) {
      println(-1);
      return;
  }
  FOR(i, 0, tt) {
    println(s[i], t[i]);
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

