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
vector<pii> g[N];
int h[N];
int n, m;
i64 d[N];
bool vis[N];
priority_queue<pair<i64, int> > pq;

inline void solve() {
  rd(n, m);
  FOR(i, 1, n + 1) cin >> h[i];
  FOR(i, 0, m) {
    int u, v;
    rd(u, v);
    g[u].eb(v, max(h[v] - h[u], 0));
    g[v].eb(u, max(h[u] - h[v], 0));
  }
  FOR(i, 1, n + 1) d[i] = 1e17;
  d[1] = 0;
  pq.push({0, 1});
  while (!pq.empty()) {
    int u = pq.top().se; pq.pop();
    if (vis[u]) continue;
    vis[u] = 1;
    for (auto [v, w] : g[u]) if (!vis[v]) {
      if (d[v] > d[u] + w) {
        d[v] = d[u] + w;
        pq.push({-d[v], v});
      }
    }
  }
  i64 ans = 0;
  FOR(i, 1, n + 1) chkmax(ans, h[1] - h[i] - d[i]);
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

