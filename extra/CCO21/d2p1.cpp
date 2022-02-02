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
const int N = 2e5+5;
int n, m;
vector<int> rg[N];
int deg[N];
struct Edge {
  int u, v, r, p, id;
  bool operator<(const Edge &rhs) const {
    return r < rhs.r;
  }
} a[N];
istream& operator>> (istream &f, Edge& a) {
  return f >> a.u >> a.v >> a.r >> a.p;
}
int ans[N];

int qu[N], hd, tl;
bool vis[N];
priority_queue<Edge> pq;

inline void del() {
  while (hd <= tl) {
    int u = qu[hd++];
    for (auto to : rg[u]) if (!vis[to]) {
      --deg[a[to].u];
      chkmin(ans[a[to].u], max(a[to].r, ans[u] - a[to].p));
      vis[to] = 1;
      if (deg[a[to].u] == 0) qu[++tl] = a[to].u;
    }
  }
}

inline void solve() {
  rd(n, m);
  FOR(i, 1, m + 1) cin >> a[i];
  FOR(i, 1, m + 1) rg[a[i].v].pb(i), a[i].id = i, ++deg[a[i].u];
  hd = 1, tl = 0;
  FOR(i, 1, n + 1) if (deg[i] == 0) qu[++tl] = i;
  del();
  FOR(i, 1, m + 1) if (!vis[i]) pq.push(a[i]);
  FOR(i, 1, n + 1) ans[i] = 1e9+7;
  while (!pq.empty()) {
    auto e = pq.top();pq.pop();
    if (vis[e.id]) continue;
    if (deg[e.u] == 1) {
      chkmin(ans[e.u], e.r);
      qu[++tl] = e.u;
    }
    --deg[e.u];
    vis[e.id] = 1;
    del();
  }
  FOR(i, 1, n + 1) cout << (ans[i] == 1e9+7 ? -1 : ans[i]) << " \n"[i==n];
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

