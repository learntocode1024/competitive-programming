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
vector<int> g[N];
bool v[N];
int dp[N], cv;

inline void solve() {
  rd(n, m);
  FOR(i, 0, m) {
    int u, v;
    rd(u, v);
    if (v < u) swap(u, v);
    g[u].pb(v);
  }
  FOR(i, 2, n + 1) dp[i] = 1e8;
  int r = -1;
  for (int i = 1; i < n; ++i) {
    chkmin(dp[i], dp[i-1] + 1);
    cv += !v[i];
    v[i] = 1;
    for (auto to : g[i]) cv += !v[to], v[to] = 1, chkmax(r, to);
    chkmax(r, i+1);
    chkmin(dp[r], dp[i] + r - cv);
    dp[1] = 1e8;
  }
  println(dp[n]);
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

