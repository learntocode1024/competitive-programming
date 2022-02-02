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
int ans[N];
int l[N], r[N], tot;
int n, q;
bool vis[N];
int a[N];
queue<int> Q;

inline void solve() {
  cin >> n >> q;
  FOR(i, 1, n + 1) a[i] = q;
  FOR(i, 1, q + 1) {
    char op;
    cin >> op;
    if (op == 'A') {
      l[++tot] = i;
      int u, v;
      cin >> u >> v;
      g[u].eb(v, tot);
      g[v].eb(u, tot);
    } else if (op == 'R') {
      int e;
      cin >> e;
      r[e] = i;
    } else {
      int x;
      cin >> x;
      a[x] = i - 1;
    }
  }
  for (int t = 1; t <= q; ++t) {
    FOR(i, 1, n + 1) if (a[i] >= t) Q.push(i), vis[i] = 1;
    while (!Q.empty()) {
      int u = Q.front(); Q.pop();
      for (auto [v, id] : g[u]) if (!vis[v] && l[id] <= t && r[id] > t) vis[v] = 1, Q.push(v);
    }
    FOR(i, 1, n + 1) if (vis[i]) chkmax(ans[i], t), vis[i] = 0;
  }
  FOR(i, 1, n + 1) println(ans[i]);
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

