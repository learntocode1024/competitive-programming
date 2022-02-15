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
int deg[N], h[N];
vector<int> g[N];
bool vis[N];
int n;
priority_queue<pii, vector<pii>, greater<pii> > pq;

inline void solve() {
  i64 ans = 0;
  int H = 0;
  rd(n);
  FOR(i, 1, n + 1) cin >> h[i];
  FOR(i, 1, n) {
    int u, v;
    rd(u, v);
    ++deg[u], ++deg[v];
    g[u].pb(v);
    g[v].pb(u);
  }
  int cnted = 0;
  FOR(i, 1, n + 1) if (deg[i] == 1) pq.push(mkp(h[i], i)), vis[i] = 1, ++cnted;
  while (!pq.empty()) {
    while (!pq.empty() && pq.top().fi <= H) {
      int u = pq.top().se;
      pq.pop();
      for (auto v : g[u]) if (!vis[v]) {
        --deg[v];
        if (deg[v] == 1) vis[v] = 1, pq.push(mkp(h[v], v)), ++cnted;
      }
    }
    if (pq.empty()) break;
    int I = pq.top().fi;
    if (pq.size() == 1 && cnted == n) {
      ans += 2 * (I - H);
      H = I;
      continue;
    }
    ans += 1ll * pq.size() * (I - H);
    H = I;
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

