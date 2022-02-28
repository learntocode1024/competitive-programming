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
const int N = 20, M = 105;
int f1[M], f2[M], b1[M], b2[M], w[M];
char s[M], t[M];
int n, m;
int dist[1<<N];
bool vis[1<<N];
vector<pii> g[1<<N];
priority_queue<pii, vector<pii>, greater<pii> > pq;

inline void solve() {
  rd(n, m);
  FOR(i, 0, m) {
    rd(w[i], s, t);
    FOR(j, 0, n) {
      if (s[j] == '+') b1[i] |= 1 << j;
      if (s[j] == '-') b2[i] |= 1 << j;
      if (t[j] == '-') f1[i] |= 1 << j;
      if (t[j] == '+') f2[i] |= 1 << j;
    }
  }
  FOR(i, 0, 1 << n) {
    FOR(j, 0, m) {
      if (((b1[j] & i) == b1[j]) && ((b2[j] & ~i) == b2[j])) {
        g[i].eb((i & (~f1[j])) | f2[j], w[j]);
      }
    }
  }
  FOR(i, 0, 1 << n) dist[i] = 1e9;
  int src = (1 << n) - 1;
  dist[src] = 0;
  pq.push({0, src});
  while (!pq.empty()) {
    int u = pq.top().se; pq.pop();
    if (vis[u]) continue;
    vis[u] = 1;
    for (auto v : g[u]) {
      if (dist[v.fi] > dist[u] + v.se) {
        dist[v.fi] = dist[u] + v.se;
        pq.push({dist[v.fi], v.fi});
      }
    }
  }
  if (dist[0] == 1e9) dist[0] = 0;
  println(dist[0]);
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

