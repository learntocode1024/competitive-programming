#include <bits/stdc++.h>
#include "atcoder/maxflow"
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
const int N = 105;

inline void solve() {
  int n, m;
  rd(n, m);
  atcoder::mf_graph<i64> g(n*2+1);
  FOR(i, 1, m + 1) {
    int u, v;
    rd(u, v);
    g.add_edge(u*2-1, v*2, 1e17);
    g.add_edge(v*2-1, u*2, 1e17);
  }
  FOR(i, 1, n + 1) {
    int c;
    rd(c);
    if (i != 1 && i != n) {
      g.add_edge(i*2, i*2-1, c);
    }
  }
  println(g.flow(1, n*2));
  auto ret = g.min_cut(1);
  int cnt = 0;
  FOR(i, 2, n) {
    if (ret[i*2]^ret[i*2-1]) ++cnt;
  }
  println(cnt);
  FOR(i, 2, n) {
    if (ret[i*2]^ret[i*2-1]) cout << i << ' ';
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

